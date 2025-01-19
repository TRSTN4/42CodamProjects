// src/components/ChatPage.tsx

import React, { useState, useEffect } from "react";
import Chat from "../components/chat/Chat";
import axiosInstance from "../components/utils/AxiosInstance";
import SpinningLogo from "../components/SpinningLogo";

interface ChatPageProps {
  userId: number;
}

const ChatPage: React.FC<ChatPageProps> = ({ userId }) => {
  const [username, setUsername] = useState<string>("");
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    const fetchUser = async () => {
      try {
        const response = await axiosInstance.get(`/users/${userId}/`);
        if (response.status === 200 && response.data)
          setUsername(response.data.username);
        setIsConnected(true);
      } catch (error) {
        console.error("Failed to fetch user data", error);
      }
    };

    fetchUser();
  }, [userId]);

  if (username === "" || !isConnected) return <SpinningLogo />;

  return (
    <div className="d-flex" style={{ height: "100vh" }}>
      <Chat username={username} />
    </div>
  );
};

export default ChatPage;
