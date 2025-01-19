from django.http import Http404
from rest_framework.parsers import JSONParser
from rest_framework.response import Response
from .models import PongUser, OTP, MatchHistory
from friends.models import FriendRequest
from .serializers import UserSerializer, LoginSerializer, MatchHistorySerializer
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth import authenticate
from rest_framework_simplejwt.tokens import AccessToken, RefreshToken
from django.db import transaction
from rest_framework.views import APIView
from django.core.mail import send_mail
from django.conf import settings
from rest_framework import status, viewsets
from django.shortcuts import get_object_or_404
from django.http import HttpResponseRedirect
from rest_framework.renderers import JSONRenderer
from django.db import IntegrityError
from rest_framework.permissions import AllowAny, IsAuthenticated
import requests
from .authentication import CookieJWTAuthentication
from rest_framework import generics

class get_users(APIView):
	permission_classes = [AllowAny]
	def get(self, request, *args, **kwargs):
		users = PongUser.objects.all()
		serializer = UserSerializer(users, many=True)
		return Response(serializer.data, status=status.HTTP_200_OK)

class user_register(APIView):
	permission_classes = [AllowAny]
	def post(self, request, *args, **kwargs):
		serializer = UserSerializer(data=request.data)
		if serializer.is_valid():

			user_data = serializer.validated_data
			password = user_data.pop('password')

			request.session['pending_user_data'] = {
				'username': user_data['username'],
				'email': user_data['email'],
				'firstName': user_data['firstName'],
				'password': password,
				'twoFactorEnabled': user_data['twoFactorEnabled'],
			}

			if user_data['twoFactorEnabled'] == True:
				otp = OTP.generate_code(email=user_data['email'])
				send_otp_email(user_data['email'], otp)
				return Response({
					"message": "Sent OTP code to email",
					"email": user_data['email']
				}, status=status.HTTP_202_ACCEPTED)
			
			user = PongUser.objects.create_user(username=user_data['username'], email=user_data['email'], password=password, firstName=user_data['firstName'], twoFactorEnabled=user_data['twoFactorEnabled'])
			return jwtCookie(user)
		return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class user_login(APIView):
	#logs a user in
	permission_classes = [AllowAny]
	def post(self, request, *args, **kwargs):
		serializer = LoginSerializer(data=request.data)
		if serializer.is_valid():
			user = authenticate_user(request, serializer)
			if user:
				if user.twoFactorEnabled:
					request.session['pending_user_id'] = user.id
					request.session['pending_user_email'] = user.email
					otp = OTP.generate_code(user.email)
					send_otp_email(user.email, otp)
					return Response({
						"message": "Sent OTP code to email",
						"email": user.email
					}, status=status.HTTP_202_ACCEPTED)
				return jwtCookie(user)
		return Response({"error": "Invalid credentials"}, status=status.HTTP_401_UNAUTHORIZED)

def jwtCookie(user):
		if user:
			refresh = RefreshToken.for_user(user)

			response = Response({
				'user_id': user.id,
				'message': "Logged in successfully",
			}, status=status.HTTP_200_OK)

			response.set_cookie(
				'access_token',
				str(refresh.access_token),
				max_age=3600, # 1 hour
				httponly=True,
				secure=True, 
				samesite='Lax',
			)

			response.set_cookie(
				'refresh_token',
				str(refresh),
				max_age=86400 , # 1 day
				httponly=True,
				secure=True,
				samesite='Lax',
			)
			return response
		else:
			return Response({"error": "Invalid credentials"}, status=status.HTTP_401_UNAUTHORIZED)
		
class verify_user(APIView):
	permission_classes = [AllowAny]
	def get(self, request):
		auth = CookieJWTAuthentication()
		user_token_pair = auth.authenticate(request)

		if user_token_pair is None:
			refresh_token = request.COOKIES.get('refresh_token')
			if not refresh_token:
				return self.logout(request)
			try:
				new_token = RefreshToken(refresh_token)
				response = Response({
					"message": "Token refreshed successfully",
				}, status=status.HTTP_200_OK)
				response.set_cookie(
					'access_token',
					str(new_token.access_token),
					max_age=3600, # 1 hour
					httponly=True,
					secure=True,  # HTTPS only, doesnt work when testing locally
					samesite='Lax',
				)
				return response
			except Exception as e:
				return self.logout(request)
			
	def logout(self, request):
		response = HttpResponseRedirect(f"{settings.FRONTEND_URL}/")
		response.delete_cookie('access_token')
		response.delete_cookie('refresh_token')
		return response

def user_42_login(request):
	authorization_url = f"{settings.AUTHORIZATION_URL}?client_id={settings.CLIENT_ID}&redirect_uri={settings.REDIRECT_URI}&response_type=code"
	return HttpResponseRedirect(authorization_url)

def user_42_callback(request):
	# Get the authorization code from the query string
	authorization_code = request.GET.get('code')

	if not authorization_code:
		return HttpResponseRedirect({f"{settings.FRONTEND_URL}/42-callback?error=authorization code not found"}, status=400)

	# Exchange the authorization code for an access token from the 42 API
	try:
		token_response = requests.post(settings.TOKEN_URL, data={
			'grant_type': 'authorization_code',
			'client_id': settings.CLIENT_ID,
			'client_secret': settings.CLIENT_SECRET,
			'code': authorization_code,
			'redirect_uri': settings.REDIRECT_URI,
		})
		token_response.raise_for_status()
		access_token = token_response.json().get('access_token')
		user_response = requests.get(settings.USER_URL, headers={
			'Authorization': f"Bearer {access_token}",
		})
		user_response.raise_for_status()
		user_data = user_response.json()

		try:
			user, created = PongUser.objects.get_or_create(
				oauth_id=user_data['id'],
				defaults={
					'username': user_data['login'],
					'email': user_data['email'],
					'firstName': user_data['first_name'],
					'twoFactorEnabled': False,
				})
			request.session['pending_user_id'] = user.id
			request.session['pending_user_email'] = user.email
		except IntegrityError:
			return HttpResponseRedirect(f"{settings.FRONTEND_URL}/42-callback?error=42_user_exists")
		if user.twoFactorEnabled:
			otp = OTP.generate_code(user.email)
			send_otp_email(user.email, otp)
			return HttpResponseRedirect(f"{settings.FRONTEND_URL}/42-callback?message=Sent OTP code to email&email={user.email}&status_code=202")
		
		refresh = RefreshToken.for_user(user)
		response = HttpResponseRedirect(f"{settings.FRONTEND_URL}/42-callback?user_id={user.id}&status_code=200")
		response.set_cookie(
			'access_token',
			str(refresh.access_token),
			max_age=3600, # 1 hour
			httponly=True,
			secure=True,  # HTTPS only, doesnt work when testing locally
			samesite='Lax',
		)
		response.set_cookie(
			'refresh_token',
			str(refresh),
			max_age=86400 , # 1 day
			httponly=True,
			secure=True,  # HTTPS only, doesnt work when testing locally
			samesite='Lax',
		)
		return response	
	except requests.exceptions.RequestException as e:
		return HttpResponseRedirect(f"{settings.FRONTEND_URL}/42-callback?error=42_login_failed")
	

def authenticate_user(request, serializer):
	username = serializer.validated_data['username']
	password = serializer.validated_data['password']
	user = authenticate(request, username=username, password=password)
	return user


def send_otp_email(email, otp):
	subject = "Your OTP code"
	message = f"Your One-Time-Password code is {otp.code}"
	recipients = [email]
	send_mail(subject, message, settings.EMAIL_HOST_USER, recipients)

class resend_otp(APIView):
	permission_classes = [AllowAny]
	def get(self, request, *args, **kwargs):
		user_data = request.session.get('pending_user_data')
		user_id = request.session.get('pending_user_id')
		user_email = request.session.get('pending_user_email')
		if user_data:
			email = user_data['email']
		elif user_id:
			email = user_email
		else:
			return Response({
				"error": "No pending user data found"
				}, status=status.HTTP_400_BAD_REQUEST)
		OTP.objects.filter(email=email).delete()
		otp = OTP.generate_code(email=email)
		send_otp_email(email, otp)
		return Response({
			"message": "Sent OTP code to email",
			"email": email
		}, status=status.HTTP_202_ACCEPTED)

class verify_otp(APIView):
	permission_classes = [AllowAny]
	def post(self, request, *args, **kwargs):
		otp_code = request.data.get('otp_code')
		user_data = request.session.get('pending_user_data')
		user_id = request.session.get('pending_user_id')
		user_email = request.session.get('pending_user_email')

		if not otp_code:
			return Response({"error": "OTP code is required"}, status=status.HTTP_400_BAD_REQUEST)

		if user_data:
			otp = OTP.objects.filter(email=user_data['email'], code=otp_code).last()
			
			if otp and not otp.is_expired():
				otp.delete()
				user = PongUser.objects.create_user(username=user_data['username'], email=user_data['email'], password=user_data['password'], firstName=user_data['firstName'], twoFactorEnabled=user_data['twoFactorEnabled'])
				request.session.pop('pending_user_data', None)
				return jwtCookie(user)
			return Response({"error": "Invalid or expired OTP code"}, status=status.HTTP_400_BAD_REQUEST)
		
		elif user_id:
			try:
				user = PongUser.objects.get(id=user_id)
				otp = OTP.objects.filter(email=user_email, code=otp_code).last()
				if otp and not otp.is_expired():
					otp.delete()
					request.session.pop('pending_user_id', None)
					request.session.pop('pending_user_email', None)
					return jwtCookie(user)
				return Response({"error": "Invalid or expired OTP code"}, status=status.HTTP_400_BAD_REQUEST)
			except PongUser.DoesNotExist:
				return Response({"error": "User not found"}, status=status.HTTP_404_NOT_FOUND)
		return Response({"error": "No pending user data found"}, status=status.HTTP_400_BAD_REQUEST)

class get_logged_in_user(APIView):
	def get(self, request):
		user_id = request.user.id
		username = request.user.username
		return Response({"user_id": user_id, "username": username}, status=status.HTTP_200_OK)

class user_detail(APIView):
	def get(self, request, pk, *args, **kwargs):
		user = get_object_or_404(PongUser, pk=pk)
		serializer = UserSerializer(user)
		return Response(serializer.data, status=status.HTTP_200_OK)
	def patch(self, request, pk, *args, **kwargs):
		user = get_object_or_404(PongUser, pk=pk)
		serializer = UserSerializer(user, data=request.data, partial=True)  # Partial update
		if serializer.is_valid():
			serializer.save()
			return Response(serializer.data, status=status.HTTP_200_OK)
		return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
	#temporary function, users can delete other users accounts
	def delete(self, request, pk):
		user = get_object_or_404(PongUser, pk=pk)
		user.delete()
		return Response("User account has been succesfully deleted", status.HTTP_204_NO_CONTENT)
	
class get_match_history(APIView):
	def get(self, request, pk):
		player = get_object_or_404(PongUser, pk=pk);
		matchhistory_models = MatchHistory.objects.filter(player=player).order_by('-date_played')
		matchhistory = MatchHistorySerializer(matchhistory_models, many=True)
		return Response(matchhistory.data, status.HTTP_200_OK)

	
class logout(APIView):
	def delete(self, request):
		response = HttpResponseRedirect(f"{settings.FRONTEND_URL}/")
		response.delete_cookie('access_token')
		response.delete_cookie('refresh_token')
		return response