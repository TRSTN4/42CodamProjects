from django.urls import re_path
from .consumers import PongConsumer
from django.urls import path
from .consumers import TournamentConsumer

websocket_urlpatterns = [
    re_path('ws/pong/$', PongConsumer.as_asgi()),
	path("ws/tournament/", TournamentConsumer.as_asgi()),
]
