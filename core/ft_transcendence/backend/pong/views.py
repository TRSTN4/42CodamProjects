from django.http import JsonResponse
from .consumers import GameManager
from rest_framework.decorators import api_view
from rest_framework.response import Response
from .tournament_manager import TournamentManager
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync

@api_view(['GET'])
def get_tournament(request):
    manager = TournamentManager.get_instance()
    tournament = manager.get_tournament()
    if not tournament:
        return Response({"message": "No active tournament"}, status=404)
    return Response(tournament)

@api_view(['POST'])
def create_tournament(request):
    organizer = request.user.username
    manager = TournamentManager.get_instance()
    try:
        result = manager.create_tournament(organizer)
        if "error" in result:
            return Response({"message": result["error"]}, status=400)   
    except Exception as e:
        print("Error creating tournament:", str(e))
        return Response({"message": "Error creating tournament"}, status=500)
    return Response(result)

@api_view(['POST'])
def sign_in_to_tournament(request):
    username = request.user.username
    manager = TournamentManager.get_instance()
    tournament = manager.get_tournament()

    if not tournament:
        return Response({"message": "No active tournament"}, status=404)

    display_name = request.data.get("display_name", "")

    try:
        if username in tournament.get("players", []):
            result = manager.unsign_player(username)
        else:
            if not display_name.strip():
                return Response({"message": "Missing or empty display_name."}, status=400)
            result = manager.sign_in_player(username, display_name)
    except Exception as e:
        print("Error toggling sign-in:", str(e))
        return Response({"message": "Error toggling sign-in"}, status=500)

    if "error" in result:
        return Response({"message": result["error"]}, status=400)
    return Response(result)

def list_lobbies(request):
    gm = GameManager.get_instance()
    lobbies = []
    for game_id, game in gm.games.items():
        lobbies.append({
            "game_id": game_id,
            "players_count": len(game.players),
            "players": game.players
        })
    return JsonResponse(lobbies, safe=False)

@api_view(['POST'])
def play_match(request):
    username = request.user.username
    match_id = request.data.get("match_id")

    manager = TournamentManager.get_instance()
    tournament = manager.get_tournament()

    if not tournament or not tournament.get("is_started"):
        return Response({"error": "Tournament not started"}, status=400)

    match = next((m for m in tournament["matches"] if m["id"] == match_id), None)
    if not match:
        return Response({"error": "Match not found"}, status=404)

    if username not in match["players"]:
        return Response({"error": "User not authorized to play this match"}, status=403)

    if "game_id" not in match:
        match["game_id"] = f"game_{match_id}"

    # Replaced with async call:
    async_to_sync(manager.broadcast_update_async)()

    return Response({
        "message": "Match started",
        "game_id": match["game_id"],
        "match_id": match_id
    })

@api_view(['GET'])
def get_username(request):
    if not request.user.is_authenticated:
        return Response({"error": "User is not authenticated"}, status=401)
    return Response({"username": request.user.username})

@api_view(['POST'])
def assign_game(request):
    match_id = request.data.get("match_id")
    manager = TournamentManager.get_instance()

    tournament = manager.get_tournament()
    if not tournament:
        return Response({"error": "No active tournament"}, status=400)

    match = next((m for m in tournament["matches"] if m["id"] == match_id), None)
    if not match:
        return Response({"error": "Match not found"}, status=400)

    if "game_id" not in match:
        result = manager.assign_game_to_match(match_id)
        if "error" in result:
            return Response({"error": result["error"]}, status=400)
        game_id = result["game_id"]
    else:
        game_id = match["game_id"]

    # Replaced with async call:
    async_to_sync(manager.broadcast_update_async)()

    return Response({
        "message": "Game assigned",
        "game_id": game_id,
        "match_id": match_id
    })

@api_view(['POST'])
def update_match_result(request):
    match_id = request.data.get("match_id")
    winner = request.data.get("winner")

    manager = TournamentManager.get_instance()
    # If you have an updated manager.update_match_result, ensure you call it properly:
    result = manager.update_match_result(match_id, winner)

    if "error" in result:
        return Response({"error": result["error"]}, status=400)
    return Response(result)

@api_view(["POST"])
def close_tournament(request):
    manager = TournamentManager.get_instance()
    tournament = manager.get_tournament()

    if not tournament:
        return Response({"error": "No active tournament"}, status=400)

    if tournament["organizer"] != request.user.username:
        return Response({"error": "Only the organizer can close the tournament"}, status=403)

    result = manager.close_tournament()
    return Response(result)
