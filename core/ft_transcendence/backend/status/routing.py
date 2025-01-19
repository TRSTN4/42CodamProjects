from django.urls import re_path
from . import consumers

websocket_urlpatterns = [
    re_path(r'ws/online_status/$', consumers.StatusConsumer.as_asgi()),
]
