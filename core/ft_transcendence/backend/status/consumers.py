from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from urllib.parse import parse_qs
from users.models import PongUser

class StatusConsumer(AsyncWebsocketConsumer):
	async def connect(self):
		await self.accept()
		query_params = parse_qs(self.scope["query_string"].decode())
		self.username = query_params.get("username", [None])[0]
		print("user connecting in websocket consumer: " + self.username)
		self.status = True
		await self.set_status()

	async def disconnect(self, close_code):
		print("disconnecting with the online-status consumer")
		self.status = False
		await self.set_status()

	@database_sync_to_async
	def set_status(self):
		try:
			user = PongUser.objects.get(username=self.username)
		except:
			self.close
		user.onlineStatus = self.status
		user.save(update_fields=["onlineStatus"])