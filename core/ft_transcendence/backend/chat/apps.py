from django.apps import AppConfig

class ChatConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'chat'

    # def ready(self):
    #    if not Room.objects.filter(name="globalRoom").exists():
    #         Room.objects.create(name="globalRoom")

