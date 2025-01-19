from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework.permissions import AllowAny

class CookieJWTAuthentication(JWTAuthentication):
    def authenticate(self, request):
        if self._is_allow_any(request):
            return None

        jwt_token = request.COOKIES.get('access_token')  # Get the token from the cookie
        if jwt_token:
            return self.get_user_and_token(jwt_token)
        return None

    def get_user_and_token(self, raw_token):
        validated_token = self.get_validated_token(raw_token)
        return self.get_user(validated_token), validated_token

    def _is_allow_any(self, request):
        """
        Determine if the current request is for a view with AllowAny permissions.
        """
        resolver_match = request.resolver_match
        if not resolver_match:
            return False

        view = resolver_match.func.view_class  # Get the view class
        if not view:
            return False

        for permission in getattr(view, 'permission_classes', []):
            if issubclass(permission, AllowAny):
                return True
        return False