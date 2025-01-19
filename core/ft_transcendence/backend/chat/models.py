from django.db import models
from users.models import PongUser

class Message(models.Model):
    sender = models.ForeignKey(
        PongUser, related_name='sent_messages', on_delete=models.CASCADE, null=True, blank=True
    )  # Allow null for announcements
    recipient = models.ForeignKey(
        PongUser, related_name='received_messages', null=True, blank=True, on_delete=models.CASCADE
    )
    text = models.TextField()
    timestamp = models.DateTimeField(auto_now_add=True)
    is_announcement = models.BooleanField(default=False)

    def __str__(self):
        if self.is_announcement:
            return f'Announcement: {self.text}'
        elif self.recipient:
            return f'DM from {self.sender} to {self.recipient}: {self.text}'
        return f'{self.sender}: {self.text}'
