import React, { useEffect, useState } from "react";
import axiosInstance from "../components/utils/AxiosInstance";
import "../css/UserProfile.css";
import { Link } from "react-router-dom";
import SpinningLogo from "../components/SpinningLogo";
import {
  sendFriendRequest,
  removeFriend,
  getFriendRequests,
  acceptFriendRequest,
} from "../components/friends/friendRequestApi";

interface User {
  id: number;
  firstName: string;
  username: string;
  avatar: string;
  friends?: number[];
  onlineStatus: boolean;
}

interface FriendRequest {
  id: number;
  sender: number;
  receiver: number;
}

const UsersPage: React.FC = () => {
  const [currentUserId, setCurrentUserId] = useState<number | null>(null);
  const [currentUser, setCurrentUser] = useState<User | null>(null);
  const [friendRequests, setFriendRequests] = useState<FriendRequest[]>([]);
  const [users, setUsers] = useState<User[]>([]);
  const [avatars, setAvatars] = useState<Record<number, string>>({});
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);
  const [searchQuery, setSearchQuery] = useState<string>("");

  useEffect(() => {
    const fetchCurrentUserId = async () => {
      try {
        const response = await axiosInstance.get<{ user_id: number }>(
          "/users/me/"
        );
        setCurrentUserId(response.data.user_id);
      } catch (err) {
        setError("Failed to load current user.");
        console.error(err);
      }
    };

    const fetchUsers = async () => {
      try {
        const response = await axiosInstance.get<User[]>("/users/");
        setUsers(response.data);
      } catch (err) {
        setError("Failed to load users.");
        console.error(err);
      } finally {
        setLoading(false);
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

    fetchCurrentUserId();
    fetchUsers();
    fetchFriendRequests();

    const interval = setInterval(() => {
      refreshFriendRequests();
      refreshUsers();
    }, 5000);

    return () => clearInterval(interval);
  }, []);

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
    const fetchAvatars = async () => {
      const avatarPromises = users.map(async (user) => {
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

    if (users.length > 0) {
      fetchAvatars();
    }
  }, [users]);

  const filteredUsers = users.filter(
    (user) =>
      user.firstName.toLowerCase().includes(searchQuery.toLowerCase()) ||
      user.username.toLowerCase().includes(searchQuery.toLowerCase())
  );

  const handleSearchChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setSearchQuery(e.target.value);
  };

  const handleAddFriend = async (userId: number) => {
    try {
      await sendFriendRequest(userId);
    } catch (err) {
      console.error("Failed to send friend request.", err);
    }
    refreshFriendRequests();
    refreshUsers();
  };

  const handleRemoveFriend = async (userId: number) => {
    try {
      await removeFriend(userId);
    } catch (err) {
      console.error("Failed to remove friend.", err);
    }
    refreshFriendRequests();
    refreshUsers();
  };

  const handleAcceptFriend = async (requestId: number) => {
    try {
      await acceptFriendRequest(requestId);
    } catch (err) {
      console.error("Failed to accept friend request.", err);
    }
    refreshFriendRequests();
    refreshUsers();
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

  if (!currentUserId) {
    return <SpinningLogo />;
  }

  if (error) return <div className="alert alert-danger">{error}</div>;

  return (
    <div className="container d-flex align-items-center justify-content-center">
      <div className="card profile-card mx-auto">
        <div className="card-header profile-header text-center">
          <h4 className="profile-title text-white">Users List</h4>
        </div>
        <div className="card-body profile-body">
          <div>
            <input
              type="text"
              placeholder="Search users..."
              className="form-control"
              value={searchQuery}
              onChange={handleSearchChange}
            />
          </div>
          <div className="userpage mt-3">
            <ul className="d-flex flex-column align-items-center justify-content-center">
              {filteredUsers.map((user) => {
                const isFriend =
                  currentUser?.friends?.includes(user.id) || false;

                const isPending = friendRequests.some(
                  (request) =>
                    request.sender === currentUserId &&
                    request.receiver === user.id
                );

                const incomingRequest = friendRequests.find(
                  (request) =>
                    request.sender === user.id &&
                    request.receiver === currentUserId
                );

                const isIncoming = Boolean(incomingRequest);
                const requestID = isIncoming ? incomingRequest?.id : null;

                return (
                  <Link
                    to={`/users/${user.username}`}
                    className="list-group-item list-group-item-action d-flex mt-2 users-list-body align-items-center justify-content-between link-item"
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
                          alt={`${user.username}'s avatar`}
                          className="users-avatar mt-2"
                        />
                      </div>
                      <div className="d-flex flex-column align-items-start ms-3">
                        <strong>{user.firstName}</strong>@{user.username}
                        <br />
                      </div>
                    </div>
                    <div className="d-flex ms-5">
                      {user.id !== currentUserId && (
                        <>
                          {isFriend ? (
                            <button
                              className="btn btn-danger ms-2"
                              onClick={(e) => {
                                e.preventDefault(); // Prevent the default link behavior
                                e.stopPropagation(); // Stop the event from bubbling to the Link
                                handleRemoveFriend(user.id);
                              }}
                            >
                              Remove Friend
                            </button>
                          ) : isPending ? (
                            <button
                              className="btn btn-secondary ms-2"
                              disabled
                              onClick={(e) => {
                                e.preventDefault();
                                e.stopPropagation();
                              }}
                            >
                              Pending...
                            </button>
                          ) : isIncoming && requestID ? (
                            <button
                              className="btn btn-primary ms-2"
                              onClick={(e) => {
                                e.preventDefault();
                                e.stopPropagation();
                                handleAcceptFriend(requestID);
                              }}
                            >
                              Accept
                            </button>
                          ) : (
                            <button
                              className="btn btn-success ms-2"
                              onClick={(e) => {
                                e.preventDefault();
                                e.stopPropagation();
                                handleAddFriend(user.id);
                              }}
                            >
                              Add Friend
                            </button>
                          )}
                        </>
                      )}
                    </div>
                  </Link>
                );
              })}
            </ul>
          </div>
        </div>
        <div className="card-footer profile-footer d-flex">
          Total users: {filteredUsers.length}
        </div>
      </div>
    </div>
  );
};

export default UsersPage;
