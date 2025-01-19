import React, { useEffect, useState } from "react";
import axiosInstance from "../components/utils/AxiosInstance";
import "../css/UserProfile.css";
import { Link } from "react-router-dom";
import SpinningLogo from "../components/SpinningLogo";
import {
  acceptFriendRequest,
  declineFriendRequest,
  getFriendRequests,
  removeFriend,
  cancelFriendRequest,
} from "../components/friends/friendRequestApi";

interface FriendRequest {
  id: number;
  sender: number;
  receiver: number;
}

interface User {
  id: number;
  firstName: string;
  username: string;
  avatar: string; // Path to the user's avatar (not the full URL)
  friends?: number[];
  onlineStatus: boolean;
}

const FriendPage: React.FC = () => {
  const [friendRequests, setFriendRequests] = useState<FriendRequest[]>([]);
  const [currentUserId, setCurrentUserId] = useState<number | null>(null);
  const [currentUser, setCurrentUser] = useState<User | null>(null);
  const [currentUserFriends, setCurrentUserFriends] = useState<number[]>([]);
  const [users, setUsers] = useState<Record<number, User>>({});
  const [avatarUsers, setAvatarUsers] = useState<User[]>([]);
  const [avatars, setAvatars] = useState<Record<number, string>>({});
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchCurrentUserId = async () => {
      try {
        const response = await axiosInstance.get<{
          user_id: number;
        }>("/users/me/");
        setCurrentUserId(response.data.user_id);
      } catch (err) {
        setError("Failed to load current user.");
        console.error(err);
      }
    };

    const fetchFriendRequests = async () => {
      try {
        const response = await getFriendRequests();
        setFriendRequests(response.data);
      } catch (err) {
        setError("Failed to load friend requests.");
        console.error(err);
      } finally {
        setLoading(false);
      }
    };

    const fetchUsers = async () => {
      try {
        const response = await axiosInstance.get<User[]>("/users/");
        const usersById = response.data.reduce(
          (acc, user) => ({ ...acc, [user.id]: user }),
          {}
        );
        setUsers(usersById);
      } catch (err) {
        console.error("Failed to load users.", err);
      }
    };

    const fetchAvatarUsers = async () => {
      try {
        const response = await axiosInstance.get<User[]>("/users/");
        setAvatarUsers(response.data);
      } catch (err) {
        setError("Failed to load users.");
        console.error(err);
      } finally {
        setLoading(false);
      }
    };

    fetchCurrentUserId();
    fetchFriendRequests();
    fetchUsers();
    fetchAvatarUsers();

    const interval = setInterval(() => {
      refreshFriendRequests();
      refreshUsers();
      refreshFriends();
    }, 5000);

    // Clear interval on component unmount
    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    const fetchAvatars = async () => {
      const avatarPromises = avatarUsers.map(async (user) => {
        if (!user.avatar) return;

        try {
          const response = await fetch(`${user.avatar}`);
          if (!response.ok) {
            throw new Error(`Failed to fetch avatar for user ${user.id}`);
          }
          const avatarData = await response.blob();
          const avatarUrl = URL.createObjectURL(avatarData);

          setAvatars((prevAvatars) => ({
            ...prevAvatars,
            [user.id]: avatarUrl,
          }));
        } catch (err) {
          console.error(`Error fetching avatar for user ${user.id}:`, err);
        }
      });

      await Promise.all(avatarPromises);
    };

    if (avatarUsers.length > 0) {
      fetchAvatars();
    }
  }, [users]);

  useEffect(() => {
    if (currentUserId) {
      const fetchCurrentUser = async () => {
        try {
          const response = await axiosInstance.get<User>(
            `/users/${currentUserId}/`
          );
          setCurrentUser(response.data);
        } catch (err) {
          setError("Failed to load current user.");
          console.error(err);
        }
      };

      fetchCurrentUser();
    }
  }, [currentUserId]);

  useEffect(() => {
    if (currentUser) {
      setCurrentUserFriends(currentUser.friends || []);
    }
  }, [currentUser]);

  const handleAccept = async (requestId: number) => {
    try {
      await acceptFriendRequest(requestId);
      setFriendRequests((prevRequests) =>
        prevRequests.filter((request) => request.id !== requestId)
      );
    } catch (err) {
      console.error("Failed to accept friend request.", err);
    }
    refreshFriends();
  };

  const handleDecline = async (requestId: number) => {
    try {
      await declineFriendRequest(requestId);
      setFriendRequests((prevRequests) =>
        prevRequests.filter((request) => request.id !== requestId)
      );
    } catch (err) {
      console.error("Failed to decline friend request.", err);
    }
  };

  const handleCancel = async (requestId: number) => {
    try {
      await cancelFriendRequest(requestId);
      setFriendRequests((prevRequests) =>
        prevRequests.filter((request) => request.id !== requestId)
      );
    } catch (err) {
      console.error("Failed to cancel friend request.", err);
    }
  };

  const handleRemoveFriend = async (userId: number) => {
    try {
      await removeFriend(userId);
      setCurrentUserFriends((prevFriends) =>
        prevFriends.filter((friendId) => friendId !== userId)
      );
    } catch (err) {
      console.error("Failed to remove friend.", err);
    }
    refreshFriends();
  };

  const refreshFriends = async () => {
    try {
      const response = await axiosInstance.get<User>(
        `/users/${currentUserId}/`
      );
      setCurrentUser(response.data);
    } catch (err) {
      console.error("Failed to refresh friends.", err);
    }
  };

  const refreshFriendRequests = async () => {
    try {
      const response = await getFriendRequests();
      setFriendRequests(response.data);
    } catch (err) {
      console.error("Failed to refresh friend requests.", err);
    }
  };

  const refreshUsers = async () => {
    try {
      const response = await axiosInstance.get<User[]>("/users/");
      setUsers(response.data);
    } catch (err) {
      console.error("Failed to refresh users.", err);
    }
  };

  if (loading) {
    return <SpinningLogo />;
  }

  if (error) return <div className="alert alert-danger">{error}</div>;

  const incomingRequests = friendRequests.filter(
    (request) => currentUserId && request.receiver === currentUserId
  );

  const sentRequests = friendRequests.filter(
    (request) => currentUserId && request.sender === currentUserId
  );

  const friendsList = Object.values(users).filter((user) =>
    currentUserFriends.includes(user.id)
  );

  return (
    <div className="container d-flex align-items-center justify-content-center">
      <div className="card profile-card mx-auto">
        <div className="card-header profile-header text-center">
          <h4 className="profile-title text-white">Friends</h4>
        </div>
        <div className="card-body profile-body">
          <h5>
            {friendsList.length}{" "}
            {friendsList.length === 1 ? "Friend" : "Friends"}
          </h5>

          <ul className="d-flex flex-column align-items-center justify-content-center friends-list">
            {friendsList.length > 0 ? (
              friendsList.map((user) => (
                <Link
                  to={`/users/${user.username}`}
                  key={user.id}
                  className="d-flex mt-2 users-list-body align-items-center justify-content-between link-item"
                >
                  <div className="d-flex align-items-center">
                    <div>
                      <div className="status-profile online online-profile">
                        <span
                          className={`status ${
                            user.onlineStatus ? "true" : "false"
                          }`}
                        >
                          {user.onlineStatus ? "Online" : "Offline"}
                        </span>
                      </div>
                      <img
                        src={avatars[user.id] || "/images/default_avatar.jpg"}
                        alt="User Avatar"
                        className="users-avatar"
                      />
                    </div>
                    <div className="d-flex flex-column align-items-start ms-3">
                      <strong>{user.firstName}</strong>@{user.username}
                      <br />
                    </div>
                  </div>
                  <div>
                    <button
                      className="btn btn-danger"
                      onClick={(e) => {
                        e.preventDefault();
                        e.stopPropagation();
                        handleRemoveFriend(user.id);
                      }}
                    >
                      Remove friend
                    </button>
                  </div>
                </Link>
              ))
            ) : (
              <li className="text-center">
                You currently don't have any friends. Visit the{" "}
                <Link to="/users">users page</Link> to search for them!
              </li>
            )}
          </ul>
        </div>
        <div className="card-footer profile-footer friends-list-requests">
          <h6>Incoming Requests</h6>
          <ul className="d-flex flex-column align-items-center justify-content-center">
            {incomingRequests.length > 0 ? (
              incomingRequests.map((request) => {
                const sender = users[request.sender];
                return (
                  <li
                    key={request.id}
                    className="d-flex mt-2 users-list-body align-items-center justify-content-between"
                  >
                    <div className="d-flex align-items-center">
                      From: {sender ? sender.username : "Unknown"}
                    </div>
                    <div className="d-flex ms-3">
                      <button
                        className="btn btn-primary me-2"
                        onClick={() => handleAccept(request.id)}
                      >
                        Accept
                      </button>
                      <button
                        className="btn btn-danger"
                        onClick={() => handleDecline(request.id)}
                      >
                        Decline
                      </button>
                    </div>
                  </li>
                );
              })
            ) : (
              <li className="text-center">You have no incoming requests</li>
            )}
          </ul>

          <h6 className="mt-4 friends-list-outgoing-container">
            Sent Requests
          </h6>
          <ul className="d-flex flex-column align-items-center justify-content-center">
            {sentRequests.length > 0 ? (
              sentRequests.map((request) => {
                const receiver = users[request.receiver];
                return (
                  <li
                    key={request.id}
                    className="d-flex mt-2 users-list-body align-items-center justify-content-between"
                  >
                    <div className="d-flex align-items-center">
                      To: {receiver ? receiver.username : "Unknown"}
                    </div>
                    <div>
                      <button
                        className="btn btn-danger ms-2"
                        onClick={() => handleCancel(request.id)}
                      >
                        Cancel request
                      </button>
                    </div>
                  </li>
                );
              })
            ) : (
              <li className="text-center">You have no sent requests</li>
            )}
          </ul>
        </div>
      </div>
    </div>
  );
};

export default FriendPage;
