import  { useEffect, useState } from "react";
import NotFoundPage from "../../error_pages/404NotFound";
import axiosInstance from "../utils/AxiosInstance";
import SpinningLogo from "../SpinningLogo";
import ChangeDetails from "./ChangeDetails";

// Define your axios instance

interface User {
  username: string;
  firstName: string;
  email: string;
  twoFactorEnabled: boolean;
  avatar: string;
  id: number;
}

const getUserId = async (): Promise<number | null> => {
  try {
    const response = await axiosInstance.get("/users/me/");
    const userId = response.data.user_id;

    return userId;
  } catch (error) {
    console.error("Error fetching username:", error);
    throw new Error("Unable to fetch username");
  }
};

const ChangeDetailWrapper = () => {
  const [user, setUser] = useState<User | null>(null);
  const [userId, setUserId] = useState<number | null>(null);
  const [avatar, setAvatar] = useState<string | null>(null);

  useEffect(() => {
    const fetchCurrentUser = async () => {
      const userId = await getUserId();
      setUserId(userId);
    };

    fetchCurrentUser();
  }, []);

  useEffect(() => {
    const fetchUser = async () => {
      try {
        const response = await axiosInstance.get(`/users/${userId}/`);
        if (response.status === 200 && response.data) setUser(response.data);
      } catch (error) {
        console.error("Failed to fetch user data", error);
      }
    };

    fetchUser();
  }, [userId]);

  useEffect(() => {
    const fetchAvatar = async () => {
      if (!user || !user.avatar) return; // Skip if no avatar is available

      try {
        const response = await fetch(`${user.avatar}`);
        if (!response.ok) {
          throw new Error("Failed to fetch user avatar");
        }
        const avatarData = await response.blob();
        const avatarUrl = URL.createObjectURL(avatarData);
        setAvatar(avatarUrl);

        // Debugging: Log the URL
      } catch (error) {
        console.error("Failed to fetch user avatar", error);
      }
    };

    fetchAvatar();

    return () => {
      if (avatar) {
        URL.revokeObjectURL(avatar);
      }
    };
  }, [user]);

  if (userId === null) {
    return <NotFoundPage />;
  }

  if (!userId) {
    return <SpinningLogo />;
  }

  if (!user) {
    return <SpinningLogo />;
  }

  return (
    <ChangeDetails
      username={user.username}
      firstName={user.firstName}
      email={user.email}
      twoFactorEnabled={user.twoFactorEnabled}
      avatarUrl={avatar || "/images/default_avatar.jpg"}
      userId={user.id}
    />
  );
};

export default ChangeDetailWrapper;
