import React, { useEffect, useState } from "react";
import { MatchHistory, User } from "../components/utils/api";
import "../css/UserProfile.css";
import axiosInstance from "../components/utils/AxiosInstance";
import { useAuth } from "../components/utils/AuthContext";
import { useNavigate } from "react-router-dom";
import SpinningLogo from "../components/SpinningLogo";
import { Link } from "react-router-dom";

type UserProfileProps = {
  userId: number;
};

const getCurrentUser = async (): Promise<number | null> => {
  try {
    const response = await axiosInstance.get("/users/me/");
    return response.data.user_id;
  } catch (error) {
    console.error("Failed to fetch current user:", error);
    return null;
  }
};

const UserProfile: React.FC<UserProfileProps> = ({ userId }) => {
  const navigate = useNavigate();
  const logout = useAuth().logout;

  const [user, setUser] = useState<User | null>(null);
  const [matchHistory, setMatchHistory] = useState<MatchHistory[]>([]);
  const [avatar, setAvatar] = useState<string | null>(null);
  const [error, setError] = useState<string | null>(null);
  const [currentUser, setCurrentUser] = useState<number | null>(null);

  useEffect(() => {
    const fetchCurrentUser = async () => {
      const userId = await getCurrentUser();
      setCurrentUser(userId);
    };

    fetchCurrentUser();
  }, []);

  useEffect(() => {
    const fetchUser = async () => {
      try {
        const response = await axiosInstance.get(`/users/${userId}/`);
        if (response.status === 200 && response.data) setUser(response.data);
      } catch (error) {
        setError((error as Error).message);
      }
    };

    fetchUser();

    const interval = setInterval(() => {
      refreshUser();
    }, 5000);
    return () => clearInterval(interval);
  }, [userId]);

  useEffect(() => {
    const fetchAvatar = async () => {
      if (!user || !user.avatar) return; // Skip if no avatar is available

      try {
        const response = await fetch(`${user.avatar}`);
        if (!response.ok) {
          console.error("Failed to fetch avatar:", response.statusText);
		  setAvatar("/images/default_avatar.jpg");
		  return;
        }
        const avatarData = await response.blob();
        const avatarUrl = URL.createObjectURL(avatarData);
        setAvatar(avatarUrl);

        // Debugging: Log the URL
      } catch (error) {
        setError((error as Error).message);
      }
    };

    fetchAvatar();

    // Cleanup: Revoke object URLs to prevent memory leaks
    return () => {
      if (avatar) {
        URL.revokeObjectURL(avatar);
      }
    };
  }, [user]);

  useEffect(() => {
    const fetchMatchHistory = async () => {
      try {
        const response = await axiosInstance.get<MatchHistory[]>(
          `/users/match_history/${userId}/`
        );
        if (response.status === 200 && response.data)
          setMatchHistory(response.data);
      } catch (error) {
        setError((error as Error).message);
      }
    };

    fetchMatchHistory();
  }, [userId]);

  const refreshUser = async () => {
    try {
      const response = await axiosInstance.get(`/users/${userId}/`);
      if (response.status === 200 && response.data) setUser(response.data);
    } catch (error) {
      setError((error as Error).message);
    }
  };

  if (error) return <div className="alert alert-danger">{error}</div>;
  if (!user) return <SpinningLogo />;
  //   if (currentUser === null) return <div className="text-center mt-5">Currentuser not loaded</div>;

  const logoutLink = () => {
    logout();
    setTimeout(() => navigate("/"), 1000);
    return <div>Logging out......</div>;
  };

  const returnWins = (matchHistory: { result: string }[]): number => {
    return matchHistory.filter((match) => match.result.toLowerCase() === "win")
      .length;
  };

  const returnLoss = (matchHistory: { result: string }[]): number => {
    return matchHistory.filter((match) => match.result.toLowerCase() === "loss")
      .length;
  };

  return (
    <div className="container d-flex align-items-center justify-content-center">
      <div className="card profile-card mx-auto">
        <div className="card-header profile-header text-center">
          <img
            src={avatar || "/images/default_avatar.jpg"}
            alt={`${user.firstName}'s avatar`}
            className="profile-avatar"
          />
        </div>
        <div className="card-body profile-body">
          <h4 className="profile-title">{user.firstName}</h4>
          <p className="profile-username mb-1">@{user.username}</p>
          <div className="list-group-item">
            {" "}
            <span className={`status ${user.onlineStatus ? "true" : "false"}`}>
              {user.onlineStatus ? "Online" : "Offline"}
            </span>
          </div>
          <div className="list-group profile-info">
            <div className="list-group-item">
              <strong>Email:</strong> {user.email}
            </div>

            <div className="list-group-item">
              <strong>Friends:</strong> {user.friends.length}{" "}
              {user.friends.length === 1 ? "Friend" : "Friends"}
            </div>
          </div>
        </div>
        <div className="card-footer profile-footer">
          <h5 className="match-history-title mb-1">Stats</h5>
          <ul className="list-group match-history-list">
            <li className="list-group-item d-flex justify-content-between">
              <span>Total Matches</span>
              <span className="fw-bold">{matchHistory.length}</span>
            </li>
            <li className="list-group-item d-flex justify-content-between">
              <span>Wins</span>
              <span className="fw-bold">{returnWins(matchHistory)}</span>
            </li>
            <li className="list-group-item d-flex justify-content-between">
              <span>Losses</span>
              <span className="fw-bold">{returnLoss(matchHistory)}</span>
            </li>
          </ul>
        </div>
        <div className="card-footer profile-footer">
          <h5 className="match-history-title mb-1">Match History</h5>
          <h6 className=""> Last 10 matches </h6>
          <ul className="list-group match-history-list scrollable-content">
            {matchHistory.length > 0 ? (
              matchHistory.slice(0, 10).map((match, index) => (
                <li
                  key={index}
                  className="list-group-item d-flex justify-content-between"
                >
                  <span>Opponent: {match.opponent_username}</span>
                  <span>
                    {" "}
                    <span className={`result ${match.result}`}>
                      {match.result[0].toUpperCase() + match.result.slice(1)}
                    </span>{" "}
                    on {new Date(match.date_played).toLocaleString()}
                  </span>
                </li>
              ))
            ) : (
              <li className="list-group-item text-center">No matches yet</li>
            )}
          </ul>
        </div>
        {currentUser === userId && (
          <div className="card-footer profile-footer d-flex justify-content-between">
            <Link to="/users/edit" className="btn btn-primary">
              {" "}
              Change details
            </Link>
            <button onClick={logoutLink} className="btn btn-danger">
              Log out
            </button>
          </div>
        )}
      </div>
    </div>
  );
};

export default UserProfile;
