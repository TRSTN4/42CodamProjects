import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.generic.websocket import AsyncJsonWebsocketConsumer
from asyncio import create_task, sleep
from urllib.parse import parse_qs
from django.utils.timezone import now
from asgiref.sync import sync_to_async
from users.models import PongUser, MatchHistory
from channels.db import database_sync_to_async
from asgiref.sync import async_to_sync
from channels.layers import get_channel_layer
from .tournament_manager import TournamentManager

class TournamentConsumer(AsyncJsonWebsocketConsumer):
    async def connect(self):
        await self.channel_layer.group_add("tournament_updates", self.channel_name)
        await self.accept()

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard("tournament_updates", self.channel_name)

    async def tournament_update(self, event):
        await self.send_json(event["message"])


class Game:
    def __init__(self, game_id):
        self.game_id = game_id
        self.paddles = {"a": 250, "b": 250}
        self.ball = {"x": 500, "y": 300, "dx": 1, "dy": 1}
        self.score = {"a": 0, "b": 0}
        self.MAX_SCORE = 3
        self.players = {}       # 'a' -> browser_key, 'b' -> browser_key
        self.players_info = {}  # 'a' -> {"username": "...", "display_name": "..."}
        self.game_started = False
        self.countdown_in_progress = False
        self.paddle_directions = {"a": 0, "b": 0}
        self.ready_players = {"a": False, "b": False}
        self.game_ended = False  # Prevent double match/tournament logic

    def reset_ball(self):
        # Flip direction so next serve is from the opposite side
        self.ball = {
            "x": 500,
            "y": 300,
            "dx": -1 if self.ball["dx"] > 0 else 1,
            "dy": 1
        }

    def reset_game(self):
        """Optionally used if you want to re-start after a gameOver, but we skip it here."""
        self.paddles = {"a": 250, "b": 250}
        self.score = {"a": 0, "b": 0}
        self.reset_ball()
        self.game_started = False
        self.countdown_in_progress = False
        self.paddle_directions = {"a": 0, "b": 0}
        self.ready_players = {"a": False, "b": False}
        self.game_ended = False


class GameManager:
    instance = None

    def __init__(self):
        self.games = {}
        self.game_counter = 0
        self.browser_key_to_channel = {}
        self.browser_key_to_game = {}

    @classmethod
    def get_instance(cls):
        if not cls.instance:
            cls.instance = GameManager()
        return cls.instance

    def get_or_create_game(self):
        # Return an existing game if it has a free slot and not ended
        for g_id, gm in self.games.items():
            if len(gm.players) < 2 and not gm.game_ended:
                return gm
        self.game_counter += 1
        new_id = f"game_{self.game_counter}"
        new_game = Game(new_id)
        self.games[new_id] = new_game
        return new_game

    def delete_game(self, game_id):
        if game_id in self.games:
            del self.games[game_id]


class PongConsumer(AsyncWebsocketConsumer):
    """
    A WebSocket consumer that manages a Pong game.
    - Both "normal" game end and forced game over on disconnect.
    - The first consumer to end the game writes both winner and loser stats.
    """
    async def connect(self):
        query_params = parse_qs(self.scope["query_string"].decode())
        browser_key = query_params.get("key", [None])[0]
        lobby_id = query_params.get("lobby", [None])[0]

        if not browser_key:
            await self.close()
            return

        game_manager = GameManager.get_instance()

        # Join or create the game with a specific lobby
        if lobby_id:
            if lobby_id in game_manager.games:
                game = game_manager.games[lobby_id]
                if len(game.players) >= 2:
                    await self.close()
                    return
            else:
                game = Game(lobby_id)
                game_manager.games[lobby_id] = game
        else:
            game = game_manager.get_or_create_game()

        self.game = game
        self.game_id = game.game_id
        self.game_group_name = f"game_{self.game_id}"
        self.browser_key = browser_key

        # Track user in GameManager
        game_manager.browser_key_to_channel[browser_key] = self.channel_name
        game_manager.browser_key_to_game[browser_key] = game

        # Decide which paddle (a or b) to assign
        if browser_key not in game.players.values():
            if len(game.players) < 2:
                paddle = "a" if "a" not in game.players else "b"
                game.players[paddle] = browser_key
            else:
                await self.close()
                return
        else:
            # Already assigned
            paddle = next(k for k, v in game.players.items() if v == browser_key)
        self.paddle = paddle

        # Tournament logic
        manager = TournamentManager.get_instance()
        tournament = manager.get_tournament()
        display_name_for_this_user = None
        if tournament:
            match_for_this_game = next(
                (m for m in tournament.get("matches", []) if m.get("game_id") == self.game_id),
                None
            )
            if match_for_this_game:
                # Mark match as 'in_progress'
                match_for_this_game["in_progress"] = True
                match_for_this_game["connected_count"] = match_for_this_game.get("connected_count", 0) + 1
                await manager.broadcast_update_async()
                # If the tournament has a custom display_name for this user
                display_name_for_this_user = tournament.get("display_names", {}).get(browser_key)

        # Fallback to the browser_key if no display name
        user_label = display_name_for_this_user if display_name_for_this_user else browser_key

        # Store info in the game object
        if paddle not in game.players_info:
            game.players_info[paddle] = {
                "username": browser_key,
                "display_name": user_label,
            }

        await self.accept()

        # Let the client know their assigned paddle, etc.
        await self.send(json.dumps({
            "type": "assignPaddle",
            "paddle": paddle,
            "game_id": self.game_id,
            "players": {
                pad: (game.players_info[pad]["display_name"] or game.players_info[pad]["username"])
                for pad in game.players_info
            }
        }))

        # Join the channel group for this game
        await self.channel_layer.group_add(self.game_group_name, self.channel_name)

        # Notify the group about current players
        await self.channel_layer.group_send(
            self.game_group_name,
            {
                "type": "players_connected",
                "count": len(game.players),
                "players": {
                    pad: (game.players_info[pad]["display_name"] or game.players_info[pad]["username"])
                    for pad in game.players_info
                },
            }
        )

    async def disconnect(self, close_code):
        game_manager = GameManager.get_instance()
        game = getattr(self, "game", None)

        if not game:
            return

        # If the game is already ended, do nothing special
        if game.game_ended:
            # Still remove references from manager
            if self.browser_key in game_manager.browser_key_to_channel:
                del game_manager.browser_key_to_channel[self.browser_key]
            if self.browser_key in game_manager.browser_key_to_game:
                del game_manager.browser_key_to_game[self.browser_key]
            await self.channel_layer.group_discard(self.game_group_name, self.channel_name)
            return

        # Not ended => try forced game over if appropriate
        if self.browser_key in game_manager.browser_key_to_channel:
            del game_manager.browser_key_to_channel[self.browser_key]
        if self.browser_key in game_manager.browser_key_to_game:
            del game_manager.browser_key_to_game[self.browser_key]

        if self.paddle in game.players:
            del game.players[self.paddle]
        if self.paddle in game.players_info:
            del game.players_info[self.paddle]

        remaining_players = len(game.players)
        if (game.game_started or game.countdown_in_progress):
            # If exactly 1 remains, that player is the winner
            if remaining_players == 1:
                winner_username = list(game.players.values())[0]
                loser_username = self.browser_key
                await self.channel_layer.group_send(
                    self.game_group_name,
                    {
                        "type": "game_over",
                        "winner": winner_username,
                        "loser": loser_username
                    }
                )
            elif remaining_players == 0:
                # 0 remain => no winner
                game.game_ended = True
                game_manager.delete_game(self.game_id)
        else:
            # No forced winner if game wasn't started
            if remaining_players == 0:
                game.game_ended = True
                game_manager.delete_game(self.game_id)

        await self.channel_layer.group_discard(self.game_group_name, self.channel_name)

        # Optionally update the group with who’s left
        if not game.game_ended:
            await self.channel_layer.group_send(
                self.game_group_name,
                {
                    "type": "players_connected",
                    "count": len(game.players),
                    "players": {
                        pad: (game.players_info[pad]["display_name"] or game.players_info[pad]["username"])
                        for pad in game.players_info
                    },
                }
            )

    async def receive(self, text_data):
        if not hasattr(self, "paddle"):
            return
        if self.game.game_ended:
            return  # No further actions if the game ended

        data = json.loads(text_data)
        msg_type = data.get("type")

        if msg_type == "paddleMove":
            direction_key = data.get("key")
            if direction_key == "up":
                self.game.paddle_directions[self.paddle] = -1
            elif direction_key == "down":
                self.game.paddle_directions[self.paddle] = 1

        elif msg_type == "paddleStop":
            self.game.paddle_directions[self.paddle] = 0

        elif msg_type == "playerReady":
            self.game.ready_players[self.paddle] = True
            await self.channel_layer.group_send(
                self.game_group_name,
                {
                    "type": "player_ready_state",
                    "readyPlayers": self.game.ready_players
                }
            )
            # Start countdown if both ready
            if (len(self.game.players) == 2
                    and self.game.ready_players["a"]
                    and self.game.ready_players["b"]
                    and not self.game.game_started
                    and not self.game.countdown_in_progress):
                create_task(self.start_countdown_and_start_game())

    async def players_connected(self, event):
        await self.send(json.dumps({
            "type": "playersConnected",
            "count": event["count"],
            "players": event.get("players", {})
        }))

    async def player_ready_state(self, event):
        await self.send(json.dumps({
            "type": "playerReadyState",
            "readyPlayers": event["readyPlayers"]
        }))

    async def send_update(self, event):
        await self.send(json.dumps(event["message"]))

    async def countdown(self):
        for val in [3, 2, 1, "GO!"]:
            if self.game.game_ended or len(self.game.players) < 2:
                self.game.countdown_in_progress = False
                return
            await self.channel_layer.group_send(
                self.game_group_name,
                {"type": "countdown_tick", "value": val}
            )
            await sleep(1)

    async def start_countdown_and_start_game(self):
        g = self.game
        if g.game_ended or len(g.players) < 2:
            return

        g.countdown_in_progress = True
        await self.channel_layer.group_send(
            self.game_group_name,
            {"type": "countdown_start"}
        )
        await self.countdown()

        if g.game_ended or len(g.players) < 2:
            g.countdown_in_progress = False
            return

        await self.channel_layer.group_send(
            self.game_group_name,
            {"type": "countdown_end"}
        )
        g.countdown_in_progress = False
        g.game_started = True

        self.update_ball_task = create_task(self.update_ball())
        self.broadcast_game_state_task = create_task(self.broadcast_game_state())

    async def update_ball(self):
        g = self.game
        paddle_speed = 5
        min_paddle, max_paddle = 0, 500

        while g.game_started and not g.game_ended and len(g.players) == 2:
            # Move paddles
            g.paddles["a"] += g.paddle_directions["a"] * paddle_speed
            g.paddles["b"] += g.paddle_directions["b"] * paddle_speed
            g.paddles["a"] = max(min_paddle, min(max_paddle, g.paddles["a"]))
            g.paddles["b"] = max(min_paddle, min(max_paddle, g.paddles["b"]))

            # Move ball
            g.ball["x"] += g.ball["dx"] * 5
            g.ball["y"] += g.ball["dy"] * 5

            # Bounce top/bottom
            if g.ball["y"] <= 0 or g.ball["y"] >= 570:
                g.ball["dy"] *= -1

            # Paddle collisions
            if g.ball["x"] <= 10 and g.paddles["a"] <= g.ball["y"] <= g.paddles["a"] + 100:
                g.ball["dx"] *= -1
                g.ball["dx"] *= 1.05
                g.ball["dy"] *= 1.05
            elif (g.ball["x"] >= 970
                  and g.paddles["b"] <= g.ball["y"] <= g.paddles["b"] + 100):
                g.ball["dx"] *= -1
                g.ball["dx"] *= 1.05
                g.ball["dy"] *= 1.05

            # Out of left boundary
            if g.ball["x"] < 0:
                g.score["b"] += 1
                await self.channel_layer.group_send(
                    self.game_group_name,
                    {
                        "type": "send_update",
                        "message": {
                            "type": "update",
                            "paddles": g.paddles,
                            "ball": g.ball,
                            "score": g.score,
                        }
                    }
                )
                g.reset_ball()
                # Another serve countdown
                if g.score["b"] < g.MAX_SCORE and g.score["a"] < g.MAX_SCORE:
                    await self.start_countdown_after_score()

            # Out of right boundary
            elif g.ball["x"] > 1000:
                g.score["a"] += 1
                await self.channel_layer.group_send(
                    self.game_group_name,
                    {
                        "type": "send_update",
                        "message": {
                            "type": "update",
                            "paddles": g.paddles,
                            "ball": g.ball,
                            "score": g.score,
                        }
                    }
                )
                g.reset_ball()
                if g.score["a"] < g.MAX_SCORE and g.score["b"] < g.MAX_SCORE:
                    await self.start_countdown_after_score()

            # Check game over
            if g.score["a"] >= g.MAX_SCORE or g.score["b"] >= g.MAX_SCORE:
                winner_pad = "a" if g.score["a"] >= g.MAX_SCORE else "b"
                loser_pad = "b" if winner_pad == "a" else "a"
                winner_user = g.players.get(winner_pad, "Unknown")
                loser_user = g.players.get(loser_pad, "Unknown")

                await self.channel_layer.group_send(
                    self.game_group_name,
                    {
                        "type": "game_over",
                        "winner": winner_user,
                        "loser": loser_user
                    }
                )
                break

            await sleep(1/60)

    async def start_countdown_after_score(self):
        g = self.game
        if g.game_ended or len(g.players) < 2:
            return
        g.countdown_in_progress = True
        await self.channel_layer.group_send(
            self.game_group_name,
            {"type": "countdown_start"}
        )
        await self.countdown()
        if g.game_ended or len(g.players) < 2:
            g.countdown_in_progress = False
            return
        await self.channel_layer.group_send(
            self.game_group_name,
            {"type": "countdown_end"}
        )
        g.countdown_in_progress = False

    async def broadcast_game_state(self):
        g = self.game
        while g.game_started and not g.game_ended and len(g.players) == 2:
            await self.channel_layer.group_send(
                self.game_group_name,
                {
                    "type": "send_update",
                    "message": {
                        "type": "update",
                        "paddles": g.paddles,
                        "ball": g.ball,
                        "score": g.score,
                    }
                }
            )
            await sleep(1/60)

    async def countdown_start(self, event):
        await self.send(json.dumps({"type": "countdownStart"}))

    async def countdown_end(self, event):
        await self.send(json.dumps({"type": "countdownEnd"}))

    async def countdown_tick(self, event):
        await self.send(json.dumps({
            "type": "countdown_tick",
            "value": event["value"]
        }))

    @database_sync_to_async
    def _record_match_history(self, userA, userB, resultA):
        """
        Record a single row: userA got 'resultA' (True=WIN, False=LOSS) vs userB.
        If the user is not in DB, skip silently.
        """
        try:
            if resultA:
                # userA = winner, userB = loser
                winner_obj = PongUser.objects.get(username=userA)
                loser_obj = PongUser.objects.get(username=userB)
                MatchHistory.objects.create(
                    game_id=self.game_id,
                    player=winner_obj,
                    opponent=loser_obj,
                    result=MatchHistory.WIN,
                    date_played=now()
                )
            else:
                # userA = loser, userB = winner
                loser_obj = PongUser.objects.get(username=userA)
                winner_obj = PongUser.objects.get(username=userB)
                MatchHistory.objects.create(
                    game_id=self.game_id,
                    player=loser_obj,
                    opponent=winner_obj,
                    result=MatchHistory.LOSS,
                    date_played=now()
                )
        except PongUser.DoesNotExist:
            pass

    async def game_over(self, event):
        """
        Called by group_send when the game ends (naturally or forced).
        Both consumers call this, but only the first time do we do DB/tournament logic.
        """
        winner_username = event["winner"]
        loser_username = event["loser"]

        # Stop countdown for everyone
        await self.channel_layer.group_send(
            self.game_group_name,
            {"type": "countdown_end"}
        )

        already_ended = self.game.game_ended
        self.game.game_ended = True
        self.game.game_started = False
        self.game.countdown_in_progress = False

        # If I'm the first consumer to handle this gameOver => do the DB/tournament logic for both sides
        if not already_ended:
            # Even if loser is offline, we'll record their LOSS from here
            if winner_username != "Unknown" and loser_username != "Unknown":
                # Record winner's WIN
                await self._record_match_history(winner_username, loser_username, True)
                # Record loser's LOSS
                await self._record_match_history(loser_username, winner_username, False)

            # Tournament logic
            is_tournament_game = False
            final_winner_label = winner_username
            manager = TournamentManager.get_instance()
            tournament = manager.get_tournament()
            if tournament:
                match_for_this_game = next(
                    (m for m in tournament.get("matches", []) if m.get("game_id") == self.game_id),
                    None
                )
                if match_for_this_game:
                    if match_for_this_game["winner"] is None:
                        result = await manager.update_match_result_by_game_id_async(self.game_id, winner_username)
                        if not result.get("error"):
                            is_tournament_game = True
                    else:
                        is_tournament_game = True

                    # Possibly get display name
                    winner_paddle = next((k for k, v in self.game.players.items() if v == winner_username), None)
                    if winner_paddle and winner_paddle in self.game.players_info:
                        disp = self.game.players_info[winner_paddle].get("display_name")
                        if disp:
                            final_winner_label = disp

            # Send gameOver to everyone in the group
            # (They each run their local code in game_over, but we also want them to see the final winner.)
            await self.channel_layer.group_send(
                self.game_group_name,
                {
                    "type": "send_gameover_to_client",
                    "winner_label": final_winner_label
                }
            )

            # Wait 3 sec, do redirect, then delete the game
            await sleep(3)
            if is_tournament_game:
                await self.channel_layer.group_send(
                    self.game_group_name,
                    {"type": "redirect_tournament"}
                )
            else:
                await self.channel_layer.group_send(
                    self.game_group_name,
                    {"type": "redirect_play"}
                )

            GameManager.get_instance().delete_game(self.game_id)

        else:
            # The game is already ended, so just send them the local gameOver UI
            # with the best known "winner" label
            await self.channel_layer.group_send(
                self.game_group_name,
                {
                    "type": "send_gameover_to_client",
                    "winner_label": winner_username
                }
            )

    async def send_gameover_to_client(self, event):
        """
        Actually deliver the "type: gameOver" message to the *individual* consumer.
        """
        await self.send(json.dumps({
            "type": "gameOver",
            "winner": event.get("winner_label", "Unknown")
        }))

    async def redirect_tournament(self, event):
        await self.send(json.dumps({"type": "redirectToTournament"}))

    async def redirect_play(self, event):
        await self.send(json.dumps({"type": "redirectToPlay"}))
