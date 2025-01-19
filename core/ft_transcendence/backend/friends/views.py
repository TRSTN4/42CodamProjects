from django.shortcuts import render, get_object_or_404
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework import status
from users.models import PongUser
from .models import FriendRequest
from .serializers import FriendRequestSerializer

class send_friend_request(APIView):
	def post(self, request, userId):
		sender = request.user
		receiver = get_object_or_404(PongUser, pk=userId)
		if sender == receiver:
			return Response("Sender cannot be the same as reciever", status=status.HTTP_400_BAD_REQUEST)
		friend_request, created = FriendRequest.objects.get_or_create(sender=sender, receiver=receiver)
		if created:
			friend_request.save()
			return Response("friend request send", status=status.HTTP_200_OK)
		else:
			return Response("friend request already send", status=status.HTTP_400_BAD_REQUEST)
		
class cancel_friend_request(APIView):
	def delete(self, request, requestId):
		friend_request = get_object_or_404(FriendRequest, pk=requestId)
		if request.user != friend_request.sender:
			return Response("friend request can only be canceled by the sender", status=status.HTTP_403_FORBIDDEN)
		friend_request.delete()
		return Response("friend request canceled by sender", status=status.HTTP_200_OK)
		
class accept_friend_request(APIView):
	def patch(self, request, requestId):
		friend_request = get_object_or_404(FriendRequest, pk=requestId)
		if friend_request.receiver != request.user:
			return Response("Friend request can only be accepted by the receiver", status=status.HTTP_403_FORBIDDEN)
		friend_request.isAccepted = True
		request.user.add_friend(friend_request.sender)
		friend_request.delete()
		return Response("friend request accepted")
	
class decline_friend_request(APIView):
	def delete(self, request, requestId):
		friend_request = get_object_or_404(FriendRequest, pk=requestId)
		if request.user != friend_request.receiver:
			return Response("friend request can only be declined by the receiver", status=status.HTTP_403_FORBIDDEN)
		friend_request.delete()
		return Response("friend request declined declined by receiver", status=status.HTTP_200_OK)
	
class remove_friend(APIView):
	def delete(self, request, userId):
		friend = get_object_or_404(PongUser, pk=userId)
		if friend not in request.user.friends.all():
			return Response("friend not found", status=status.HTTP_404_NOT_FOUND)
		request.user.remove_friend(userId)
		return Response("friend is removed", status=status.HTTP_204_NO_CONTENT)

class get_friend_requests(APIView):
	def get(self, request, *args, **kwargs):
		friendRequests = FriendRequest.objects.all()
		serializer = FriendRequestSerializer(friendRequests, many=True)
		return Response(serializer.data, status=status.HTTP_200_OK)