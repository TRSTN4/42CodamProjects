// src/api.ts

// src/api.ts

export type MatchHistory = {
	id: number;
	opponent: number;
	opponent_username: string;
	result: string;
	date_played: string;
  };
  
  export type User = {
	id: number;
	username: string;
	email: string;
	firstName: string;
	avatar?: string;
	onlineStatus: boolean;
	friends: number[];
	matchHistory: MatchHistory[];
	twoFactorEnabled: boolean;
  };
  
  export type FriendRequest = {
	id: number;
	sender: number;
	receiver: number;
  };