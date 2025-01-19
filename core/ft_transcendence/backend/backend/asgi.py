import os
import django
import chat.routing
import status.routing
import pong.routing
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack
from django.core.asgi import get_asgi_application
from users.authentication import CookieJWTAuthentication

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'backend.settings')
django.setup()

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": AuthMiddlewareStack(
        URLRouter(
            chat.routing.websocket_urlpatterns + pong.routing.websocket_urlpatterns + status.routing.websocket_urlpatterns
        ),
    ),
})
