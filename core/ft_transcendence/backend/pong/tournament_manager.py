import re
import itertools
import threading
import time
import uuid
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
from chat.utils import send_server_announcement

class TournamentManager:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super().__new__(cls, *args, **kwargs)
        return cls._instance

    @classmethod
    def get_instance(cls):
        if not cls._instance:
            cls._instance = cls()
        return cls._instance

    def __init__(self):
        if not hasattr(self, "initialized"):
            self.tournament = None
            self.timer_thread = None
            self.lock = threading.Lock()
            self.initialized = True

    def _generate_game_id(self) -> str:
        return f"game_{uuid.uuid4().hex[:12]}"

    def create_tournament(self, organizer):
        with self.lock:
            if self.tournament:
                return {"error": "Tournament already exists"}
            self.tournament = {
                "organizer": organizer,
                "players": [],       # just storing usernames for logic
                "display_names": {}, # { username: "CustomDisplayName" }
                "timer": 30,
                "is_started": False,
                "matches": [],
                "final_result": None,
            }
            async_to_sync(self._broadcast_update_async)()
            self._start_timer_in_thread()
        return self.tournament

    def sign_in_player(self, username, display_name):
        # Validate display_name
        if len(display_name) > 12 or not re.match(r'^[a-zA-Z0-9]*$', display_name):
            return {"error": "Display name must be alphanumeric and up to 12 characters."}

        with self.lock:
            if not self.tournament:
                return {"error": "No active tournament"}

            if username in self.tournament["players"]:
                return {"error": "You are already signed in."}

            # Enforce display_name uniqueness
            if display_name in self.tournament["display_names"].values():
                return {"error": "That display name is already taken."}

            self.tournament["players"].append(username)
            self.tournament["display_names"][username] = display_name

            async_to_sync(self._broadcast_update_async)()
        return self.tournament

    def unsign_player(self, username):
        with self.lock:
            if not self.tournament:
                return {"error": "No active tournament"}
            if username not in self.tournament["players"]:
                return {"error": "Player not signed in"}

            # Remove the player from the tournament
            self.tournament["players"].remove(username)
            
            # Remove the associated display name
            if username in self.tournament["display_names"]:
                del self.tournament["display_names"][username]

            async_to_sync(self._broadcast_update_async)()
        return self.tournament

    def _start_timer_in_thread(self):
        def countdown():
            async_to_sync(send_server_announcement)(
                "You can now sign-up for a tournament!"
            )
            while True:
                time.sleep(1)
                with self.lock:
                    if not self.tournament:
                        break
                    self.tournament["timer"] -= 1
                    async_to_sync(self._broadcast_update_async)()
                    if self.tournament["timer"] <= 0:
                        if len(self.tournament["players"]) < 2:
                            self.tournament = None
                            async_to_sync(send_server_announcement)(
                                "Tournament canceled due to insufficient players."
                            )
                        else:
                            self._start_tournament_locked()
                        async_to_sync(self._broadcast_update_async)()
                        break

        self.timer_thread = threading.Thread(target=countdown, daemon=True)
        self.timer_thread.start()


    def _start_tournament_locked(self):
        self.tournament["is_started"] = True
        players = self.tournament["players"]
        matches = []
        for i, pair in enumerate(itertools.combinations(players, 2)):
            matches.append({
                "id": i,
                "players": list(pair),
                "winner": None,
                "in_progress": False,
                "connected_count": 0,
            })
        self.tournament["matches"] = matches

        # Announce tournament start
        player_display_names = [
            self.tournament["display_names"].get(player, player) for player in players
        ]
        async_to_sync(send_server_announcement)(
            f"Tournament has started! Participants: {', '.join(player_display_names)}"
        )

    def get_tournament(self):
        with self.lock:
            return self.tournament

    def assign_game_to_match(self, match_id):
        with self.lock:
            if not self.tournament:
                return {"error": "No active tournament"}
            match = next((m for m in self.tournament["matches"] if m["id"] == match_id), None)
            if not match:
                return {"error": "Match not found"}
            if "game_id" in match:
                return {"error": "Match already has an assigned game"}

            match["game_id"] = self._generate_game_id()

            # Announce match start
            player1 = self.tournament["display_names"].get(match["players"][0], match["players"][0])
            player2 = self.tournament["display_names"].get(match["players"][1], match["players"][1])
            async_to_sync(send_server_announcement)(f"Match about to start: {player1} vs {player2}")

            async_to_sync(self._broadcast_update_async)()
            return match

    def _all_matches_completed(self):
        if not self.tournament or not self.tournament.get("matches"):
            return False
        for m in self.tournament["matches"]:
            if m["winner"] is None:
                return False
        return True

    def _compute_final_result(self):
        win_count = {}
        for m in self.tournament["matches"]:
            w = m["winner"]
            if w:
                win_count[w] = win_count.get(w, 0) + 1

        if not win_count:
            return None

        max_wins = max(win_count.values())
        winners = [p for p, cnt in win_count.items() if cnt == max_wins]

        if len(winners) == 1:
            return {"type": "winner", "usernames": winners}
        else:
            return {"type": "draw", "usernames": winners}

    def close_tournament(self):
        with self.lock:
            if self.tournament:
                async_to_sync(send_server_announcement)("Tournament has been closed by the organizer.")
            self.tournament = None
            async_to_sync(self._broadcast_update_async)()
        return {"message": "Tournament closed"}

    def send_server_announcement_sync(message):
        async_to_sync(send_server_announcement)(message)

    async def update_match_result_by_game_id_async(self, game_id, winner):
        """
        Updates the match result for a given game_id and announces it to all players.
        """
        announcements = []
        with self.lock:
            if not self.tournament:
                return {"error": "No active tournament"}

            match = next((m for m in self.tournament["matches"] if m.get("game_id") == game_id), None)
            if not match:
                return {"error": "Match not found for game_id"}

            match["winner"] = winner

            # Collect announcement about the match result
            player1 = self.tournament["display_names"].get(match["players"][0], match["players"][0])
            player2 = self.tournament["display_names"].get(match["players"][1], match["players"][1])
            winner_display = self.tournament["display_names"].get(winner, winner)

            announcements.append(
                f"Match over: {player1} vs {player2}. Winner: {winner_display}!"
            )

            # If all matches are completed, compute final results and collect relevant announcements
            if self._all_matches_completed():
                final_result = self._compute_final_result()
                self.tournament["final_result"] = final_result

                if final_result and final_result["type"] == "winner":
                    winners = [
                        self.tournament["display_names"].get(user, user)
                        for user in final_result["usernames"]
                    ]
                    announcements.append(
                        f"Tournament finished! Winner(s): {', '.join(winners)}"
                    )
                elif final_result and final_result["type"] == "draw":
                    draw_players = [
                        self.tournament["display_names"].get(user, user)
                        for user in final_result["usernames"]
                    ]
                    announcements.append(
                        f"Tournament finished in a draw! Drawn players: {', '.join(draw_players)}"
                    )

        # --------------------------
        # Now we're outside the lock
        # --------------------------

        # Actually send the announcements (await the async call)
        for ann in announcements:
            print(ann)
            await send_server_announcement(ann)

        # Broadcast the updated tournament state
        await self._broadcast_update_async()
        return {"success": True, "match": match}

    async def _broadcast_update_async(self):
        channel_layer = get_channel_layer()
        await channel_layer.group_send(
            "tournament_updates",
            {
                "type": "tournament_update",
                "message": self.tournament or {},
            },
        )

    async def broadcast_update_async(self):
        """
        Send the updated tournament state asynchronously.
        This avoids using async_to_sync in an already-async context.
        """
        channel_layer = get_channel_layer()
        if not channel_layer:
            return
        await channel_layer.group_send(
            "tournament_updates",
            {
                "type": "tournament_update",
                "message": self.tournament or {},
            },
        )
