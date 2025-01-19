from . import views
from django.urls import path

urlpatterns = [
	path('send_friend_request/<int:userId>/', views.send_friend_request.as_view()),
	path('cancel_friend_request/<int:requestId>/', views.cancel_friend_request.as_view()),
    path('accept_friend_request/<int:requestId>/', views.accept_friend_request.as_view()),
	path('decline_friend_request/<int:requestId>/', views.decline_friend_request.as_view()),
	path('remove_friend/<int:userId>/', views.remove_friend.as_view()),
    path('friend_requests/', views.get_friend_requests.as_view())
]