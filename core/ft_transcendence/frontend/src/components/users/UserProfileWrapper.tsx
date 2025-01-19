import { useParams } from "react-router-dom";
import { useEffect, useState } from "react";
import UserProfile from "../../pages/UserProfile";
import NotFoundPage from "../../error_pages/404NotFound";
import axios from "axios";
import SpinningLogo from "../SpinningLogo";
const apiBaseUrl = import.meta.env.VITE_API_BASE_URL;

// Define your axios instance

interface User {
  id: string;
  username: string;
  [key: string]: any; // Additional fields can be added if needed
}

/**
 * Fetches the user list and finds the corresponding userId for the given username.
 * @param username The username to find.
 * @returns The userId corresponding to the username, or null if not found.
 */
const getUsername = async (username: string): Promise<string | null> => {
  try {
    const response = await axios.get<User[]>(`${apiBaseUrl}/users/`);
    const userList = response.data;

    const user = userList.find((user) => user.username === username);

    return user ? user.id : null;
  } catch (error) {
    console.error("Error", error);
    throw new Error("Unable to fetch user list");
  }
};

const UserProfileWrapper = () => {
  const { username } = useParams<{ username: string }>();
  const [userId, setUserId] = useState<number | null>(0); // Number state
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchUserId = async () => {
      if (username) {
        try {
          const id = await getUsername(username);
          if (id !== null) {
            setTimeout(() => setUserId(Number(id)), 100);
          } else {
            setTimeout(() => setUserId(null), 200);
          }
        } catch (err) {
          console.error(err);
          setError("Failed to fetch user information.");
        }
      }
    };

    fetchUserId();
  }, [username]);

  if (error) {
    return <div>Error: {error}</div>;
  }

  if (userId === null) {
    return <NotFoundPage />;
  }

  if (!userId) {
    return <SpinningLogo />;
  }

  return <UserProfile userId={userId} />;
};

export default UserProfileWrapper;
