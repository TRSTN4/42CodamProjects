import React from "react";
import "../../css/chat/OnlineUsers.css";
import { useNavigate } from "react-router-dom";

interface OnlineUsersProps {
  users: string[];
  currentUser: string;
  sendDirectMessage: (user: string, message: string) => void;
  blockUser: (action: "block" | "unblock", user: string) => void;
  inviteToGame: (user: string) => void;
  viewProfile: (user: string) => void;
  blockedUsers: string[]; // Add this prop
}

const OnlineUsers: React.FC<OnlineUsersProps> = ({
  users,
  currentUser,
  sendDirectMessage,
  blockUser,
  inviteToGame,
  blockedUsers,
}) => {
  const navigate = useNavigate();

  const isBlocked = (user: string) => blockedUsers.includes(user);

  return (
    <div>
      {users.map((user) => (
        <div
          key={user}
          className={`d-flex user-item flex-column mt-3 user-card ${
            isBlocked(user) ? "blocked-user" : ""
          }`}
        >
          <span
            className={`font-weight-${
              user === currentUser ? "bold" : "normal"
            }`}
          >
            {user}
          </span>

          {user !== currentUser && (
            <div className="d-flex mt-2 user-card-item">
              <button
                className="btn btn-primary actions-button"
                disabled={isBlocked(user)} // Disable DM if the user is blocked
                onClick={() => {
                  const message = prompt(`Send a DM to ${user}:`);
                  if (message) sendDirectMessage(user, message);
                }}
              >
                DM
              </button>
              <button
                className="btn btn-primary actions-button"
                onClick={() => inviteToGame(user)}
              >
                Invite Pong
              </button>
              <button
                className="btn btn-primary actions-button"
                onClick={() => navigate(`/users/${user}`)}
              >
                Profile
              </button>
              {isBlocked(user) ? (
                <button
                  className="btn btn-warning actions-button"
                  onClick={() => {
                    if (window.confirm(`Unblock user '${user}'?`)) {
                      blockUser("unblock", user);
                    }
                  }}
                >
                  Unblock
                </button>
              ) : (
                <button
                  className="btn btn-danger actions-button"
                  onClick={() => {
                    if (window.confirm(`Block user '${user}'?`)) {
                      blockUser("block", user);
                    }
                  }}
                >
                  Block
                </button>
              )}
            </div>
          )}
        </div>
      ))}
    </div>
  );
};

export default OnlineUsers;
