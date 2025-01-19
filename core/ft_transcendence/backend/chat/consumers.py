# chat/consumers.py
import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from .models import Message
from users.models import PongUser
from django.db.models import Q

online_users = {}  # {username: channel_name}

@database_sync_to_async
def get_user(username):
    return PongUser.objects.get(username=username)

@database_sync_to_async
def create_message(sender, recipient, text, is_announcement=False):
    return Message.objects.create(sender=sender, recipient=recipient, text=text, is_announcement=is_announcement)

@database_sync_to_async
def block_user(blocker, blocked_user):
    blocker.block_user(blocked_user)
    blocker.save()

@database_sync_to_async
def unblock_user(blocker, blocked_user):
    blocker.unblock_user(blocked_user)
    blocker.save()

@database_sync_to_async
def is_user_blocked(blocker, blocked_user):
    return blocker.is_blocked(blocked_user)

from django.db.models import Q

@database_sync_to_async
def get_last_messages(user, limit=50, include_blocked=False):
    if include_blocked:
        messages = Message.objects.filter(
            Q(recipient=None) | Q(recipient=user) | Q(sender=user)
        ).order_by('-timestamp')[:limit]
    else:
        blocked_users = user.blocked_users.all()
        messages = Message.objects.filter(
            (Q(recipient=None) | Q(recipient=user) | Q(sender=user)) &
            ~Q(sender__in=blocked_users)
        ).order_by('-timestamp')[:limit]

    # Reverse messages to have the most recent at the bottom
    return [
        {
            "sender": msg.sender.username if msg.sender else "Server",  # Handle None sender
            "recipient": msg.recipient.username if msg.recipient else None,
            "text": msg.text,
            "is_dm": bool(msg.recipient),
            "is_announcement": msg.is_announcement,
            "timestamp": msg.timestamp.isoformat(),
        }
        for msg in reversed(messages)
    ]

class ChatConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        query_string = self.scope['query_string'].decode('utf-8')
        params = dict(param.split('=') for param in query_string.split('&') if '=' in param)
        self.username = params.get('username')

        if not self.username:
            await self.close()
            return

        try:
            self.user = await get_user(self.username)
        except PongUser.DoesNotExist:
            await self.close()
            return

        if self.username in online_users:
            await self.close()
            return

        await self.accept()

        online_users[self.username] = self.channel_name

        last_messages = await get_last_messages(self.user)
        await self.send(text_data=json.dumps({
            "type": "chat_history",
            "messages": last_messages,
        }))

        await self.channel_layer.group_add("global", self.channel_name)
        await self.channel_layer.group_send("global", {
            "type": "update_online_users",
            "users": list(online_users.keys()),
        })

    async def disconnect(self, close_code):
        if self.username in online_users:
            del online_users[self.username]
            print(f"User disconnected: {self.username}, Online users: {list(online_users.keys())}")

        await self.channel_layer.group_discard(
            "global",
            self.channel_name
        )

        await self.channel_layer.group_send(
            "global",
            {
                "type": "update_online_users",
                "users": list(online_users.keys()),
            }
        )

    async def game_invitation(self, event):
        sender = event["sender"]
        recipient = event["recipient"]
        game_url = event["game_url"]

        # Send the game invitation message
        await self.send(text_data=json.dumps({
            "type": "game_invitation",
            "sender": sender,
            "recipient": recipient,
            "message": f'User {sender} invited you to a match. <a href="{game_url}">Click here to join</a>',
        }))

    async def receive(self, text_data):
        data = json.loads(text_data)
        msg_type = data.get("type")

        if msg_type == "invite_to_pong":
            target_username = data.get("target_user")
            game_id = data.get("game_id")  # Shared game ID
            game_url = data.get("game_url")  # URL for the invited player

            if not target_username or not game_id or not game_url:
                await self.send(json.dumps({
                    "type": "error",
                    "message": "Invalid game invite request."
                }))
                return

            if target_username in online_users:
                target_channel = online_users[target_username]

                # Send a new type of message for game invitations
                await self.channel_layer.send(
                    target_channel,
                    {
                        "type": "game_invitation",
                        "sender": self.username,
                        "recipient": target_username,
                        "game_url": game_url,
                    }
                )

                # Notify the inviter
                await self.send(json.dumps({
                    "type": "direct_message",
                    "sender": self.username,
                    "recipient": target_username,
                    "message": "Invitation sent.",
                }))
            else:
                await self.send(json.dumps({
                    "type": "error",
                    "message": f"User '{target_username}' is offline.",
                }))

        if "command" in data:
            command = data["command"]
            target_username = data.get("target_user")
            if command == "block" and target_username:
                try:
                    target_user = await get_user(target_username)
                    await block_user(self.user, target_user)
                    await self.send(text_data=json.dumps({
                        "type": "block_success",
                        "message": f"You have blocked '{target_username}'."
                    }))
                except PongUser.DoesNotExist:
                    await self.send(text_data=json.dumps({
                        "type": "error",
                        "message": f"User '{target_username}' does not exist."
                    }))
            elif command == "unblock" and target_username:
                target_username = data.get("target_user")
                if target_username:
                    try:
                        target_user = await get_user(target_username)
                        await unblock_user(self.user, target_user)
                        await self.send(text_data=json.dumps({
                            "type": "unblock_success",
                            "message": f"You have unblocked '{target_username}'."
                        }))
                        # Fetch full chat history to include unblocked user's messages
                        last_messages = await get_last_messages(self.user, include_blocked=True)
                        await self.send(text_data=json.dumps({
                            "type": "chat_history",
                            "messages": last_messages,
                        }))
                    except PongUser.DoesNotExist:
                        await self.send(text_data=json.dumps({
                            "type": "error",
                            "message": f"User '{target_username}' does not exist."
                        }))

        if "recipient" in data:  # Check if it's a DM
            recipient_username = data["recipient"]
            message = data["message"]

            if len(message) > 200:  # Enforce message length limit
                await self.send(text_data=json.dumps({"type": "error", "message": "Message too long. Maximum length is 200 characters."}))
                return

            try:
                recipient_user = await get_user(recipient_username)
            except PongUser.DoesNotExist:
                await self.send(text_data=json.dumps({
                    "type": "error",
                    "message": f"User '{recipient_username}' does not exist."
                }))
                return

            # Use async wrapper for the is_blocked check
            if await is_user_blocked(self.user, recipient_user):
                await self.send(text_data=json.dumps({
                    "type": "error",
                    "message": f"You are blocked by '{recipient_username}'."
                }))
                return

            # Save the message in the database
            await create_message(sender=self.user, recipient=recipient_user, text=message, is_announcement=False)

            # Send the message to the recipient's channel
            if recipient_username in online_users:
                recipient_channel = online_users[recipient_username]
                await self.channel_layer.send(
                    recipient_channel,
                    {
                        "type": "direct_message",
                        "sender": self.username,
                        "recipient": recipient_username,
                        "message": message,
                    }
                )

            # Send the message back to the sender
            await self.send(text_data=json.dumps({
                "type": "direct_message",
                "sender": self.username,
                "recipient": recipient_username,
                "message": message,
            }))

        elif "message" in data:
            message = data["message"]

            if len(message) > 200:  # Enforce message length limit
                await self.send(text_data=json.dumps({"type": "error", "message": "Message too long. Maximum length is 200 characters."}))
                return
            
            await create_message(sender=self.user, recipient=None, text=message, is_announcement=False)

            await self.channel_layer.group_send(
                "global",
                {
                    "type": "chat_message",
                    "sender": self.username,
                    "message": message,
                }
            )
        elif "announce" in data:
            announcement = data["announce"]

            await create_message(sender=self.user, recipient=None, text=announcement, is_announcement=True)

            await self.channel_layer.group_send(
                "global",
                {
                    "type": "server_announcement",
                    "sender": self.username,
                    "message": announcement,
                }
            )
        elif "view_profile" in data:
            target_username = data.get("target_user")
            if target_username:
                await self.send(text_data=json.dumps({
                    "type": "view_profile",
                    "target_user": target_username,
                    "url": "https://www.nu.nl"
                }))
            else:
                await self.send(text_data=json.dumps({
                    "type": "error",
                    "message": "Missing target_user for profile viewing."
                }))
        # else:
        #     print("Received unknown message format.")
        #     await self.send(text_data=json.dumps({
        #         "type": "error",
        #         "message": "Invalid message format."
        #     }))

    async def direct_message(self, event):
        sender = event["sender"]
        recipient = event["recipient"]
        message = event["message"]

        # Send the DM to the client
        await self.send(text_data=json.dumps({
            "type": "direct",
            "sender": sender,
            "recipient": recipient,
            "message": message,
        }))

    async def chat_message(self, event):
        sender = event["sender"]
        message = event["message"]

        # Check if the current user has blocked the sender
        sender_user = await get_user(sender)
        if await is_user_blocked(self.user, sender_user):
            print(f"Message from blocked user '{sender}' ignored.")
            return

        # Send message if not blocked
        await self.send(text_data=json.dumps({
            "type": "chat",
            "sender": sender,
            "message": message,
        }))

    async def server_announcement(self, event):
        await self.send(text_data=json.dumps({
            "type": "announcement",
            "sender": event["sender"],
            "message": event["message"],
        }))

    async def update_online_users(self, event):
        users = event["users"]
        blocked_users = [user.username for user in await database_sync_to_async(list)(self.user.blocked_users.all())]

        print(f"Updating online users: {users}")

        await self.send(text_data=json.dumps({
            "type": "update_users",
            "users": users,
            "blocked_users": blocked_users,
        }))
