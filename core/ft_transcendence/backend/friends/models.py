from django.db import models
from users.models import PongUser

class FriendRequest(models.Model):
	sender = models.ForeignKey(PongUser, related_name="sent_requests", on_delete=models.CASCADE)
	receiver = models.ForeignKey(PongUser, related_name="received_requests", on_delete=models.CASCADE)
	createdAt = models.DateTimeField(auto_now_add=True)
	isAccepted = models.BooleanField(default=False)

	class Meta:
		unique_together = ["sender", "receiver"]
	
	def __str__(self):
		return f"friend request: {self.sender} -> {self.receiver} | Accepted: {self.isAccepted}"
