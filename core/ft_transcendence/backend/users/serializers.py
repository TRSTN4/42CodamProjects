from rest_framework import serializers
from .models import PongUser, MatchHistory
import re

class UserSerializer(serializers.ModelSerializer):
	password = serializers.CharField(write_only=True)

	class Meta:
		model = PongUser
		fields = ['id', 'username', 'email', 'password', 'twoFactorEnabled', 'firstName', 'friends', 'avatar', 'onlineStatus']
	
	def validate_username(self, value):
		# Max length and allowed characters
		if len(value) > 20:
			raise serializers.ValidationError("Username must be 20 characters or less.")
		if not re.match(r'^[a-zA-Z0-9\-]+$', value):
			raise serializers.ValidationError("Username must be alphanumeric or include '-'.")
		
		# Unique check
		if self.instance:
			if PongUser.objects.filter(username=value).exclude(pk=self.instance.pk).exists():
				raise serializers.ValidationError("Username must be unique.")
		else:
			if PongUser.objects.filter(username=value).exists():
				raise serializers.ValidationError("Username must be unique.")
		return value
	
	def validate_password(self, value):
		# Length
		if len(value) < 8 or len(value) > 30:
			raise serializers.ValidationError("Password must be between 8 and 30 characters.")
		
		# Special character, uppercase, lowercase, number
		if not re.search(r'[!@#$%^&*(),.?":{}|<>]', value):
			raise serializers.ValidationError("Password must contain at least one special character.")
		if not re.search(r'[A-Z]', value):
			raise serializers.ValidationError("Password must contain at least one uppercase letter.")
		if not re.search(r'[a-z]', value):
			raise serializers.ValidationError("Password must contain at least one lowercase letter.")
		if not re.search(r'[0-9]', value):
			raise serializers.ValidationError("Password must contain at least one number.")
		return value
	
	def validate_email(self, value):
		# Unique email
		if self.instance:
			if PongUser.objects.filter(email=value).exclude(pk=self.instance.pk).exists():
				raise serializers.ValidationError("Email must be unique.")
		else:
			if PongUser.objects.filter(email=value).exists():
				raise serializers.ValidationError("Email must be unique.")
		return value

	def validate_avatar(self, value):
		# Check if file is too large
		if value.size > 2 * 1024 * 1024:  # 2 MB limit
			raise serializers.ValidationError("Avatar file size must be less than 2MB.")
		
		# File type
		valid_extensions = ['jpg', 'jpeg', 'png']
		file_extension = value.name.split('.')[-1].lower()
		if file_extension not in valid_extensions:
			raise serializers.ValidationError("Avatar must be a JPG or PNG image.")

		return value

	def update(self, instance, validated_data):
		if 'password' in validated_data:
			password = validated_data.pop('password')
			instance.set_password(password)
		# Save avatar
		for attr, value in validated_data.items():
			setattr(instance, attr, value)
		instance.save()
		return instance


	def create(self, validated_data):
			# Create a new user with hashed password
			user = PongUser.objects.create_user(
				username=validated_data['username'],
				email=validated_data['email'],
				password=validated_data['password'],
				twoFactorEnabled=validated_data['twoFactorEnabled'],
				firstName=validated_data['firstName']
			)
			return user

class LoginSerializer(serializers.Serializer):
	username = serializers.CharField()
	password = serializers.CharField(write_only=True)

class MatchHistorySerializer(serializers.ModelSerializer):
    opponent_username = serializers.CharField(source='opponent.username', read_only=True)

    class Meta:
        model = MatchHistory
        fields = ['id', 'game_id', 'opponent', 'opponent_username', 'result', 'date_played']