from . import views
from django.urls import path, include

urlpatterns = [
	path('', views.get_users.as_view()),
	path('login/', views.user_login.as_view()),
	path('register/', views.user_register.as_view()),
	path('<int:pk>/', views.user_detail.as_view()),
	path('verify_otp/', views.verify_otp.as_view()),
	path('resend_otp/', views.resend_otp.as_view()),
	path('auth/verify/', views.verify_user.as_view()),
	path('me/', views.get_logged_in_user.as_view()),
	path('auth/verify/', views.verify_user.as_view()),
	path('42_login/', views.user_42_login),
	path('42_callback/', views.user_42_callback),
	path('auth/logout/', views.logout.as_view()),
	path('match_history/<int:pk>/', views.get_match_history.as_view())
]
