from chat.models import Message
from channels.layers import get_channel_layer
from asgiref.sync import sync_to_async

async def send_server_announcement(message):
    """
    Broadcast a server announcement to all chat clients and save it in the database
    without associating it with a user.
    """
    channel_layer = get_channel_layer()

    # Save the announcement to the database
    try:
        await sync_to_async(Message.objects.create)(
            sender=None,  # No sender for announcements
            text=message,
            is_announcement=True
        )
    except Exception as e:
        print(f"Error saving announcement: {e}")

    # Broadcast the announcement
    if channel_layer:
        await channel_layer.group_send(
            "global",
            {
                "type": "server_announcement",
                "sender": "Server",
                "message": message,
            }
        )
