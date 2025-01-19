from django.urls import path
from . import views

urlpatterns = [
    path('api/lobbies', views.list_lobbies, name='list_lobbies'),
    path('api/tournament/', views.get_tournament, name='get_tournament'),
    path('api/tournament/create/', views.create_tournament, name='create_tournament'),
    path('api/tournament/sign-in/', views.sign_in_to_tournament, name='sign_in_to_tournament'),
    path("api/match/play/", views.play_match, name="play_match"),
    path('api/user/me/', views.get_username, name='get_username'),
    path('api/assign-game/', views.assign_game, name='assign_game'),
    path('api/tournament/close/', views.close_tournament, name='close_tournament'),
]
