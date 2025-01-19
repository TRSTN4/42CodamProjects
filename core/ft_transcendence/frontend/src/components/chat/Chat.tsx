import React, { useState, useEffect, useRef } from "react";
import MessageList from "./MessageList";
import MessageInput from "./MessageInput";
import OnlineUsers from "./OnlineUsers";
import { v4 as uuidv4 } from "uuid";
import "../../css/chat/ChatPage.css";
const wsBaseUrl = import.meta.env.VITE_WS_BASE_URL;

interface Message {
  id: string;
  sender: string;
  message: string;
  isDM?: boolean;
  isAnnouncement?: boolean;
  recipient: string; // Ensure recipient is always defined
}

interface ChatProps {
  username: string;
}

const Chat: React.FC<ChatProps> = ({ username }) => {
  console.info("Chat.tsx: username: ", username);
  const [messages, setMessages] = useState<Message[]>([]);
  const [onlineUsers, setOnlineUsers] = useState<string[]>([]);
  const [blockedUsers, setBlockedUsers] = useState<string[]>([]);
  const ws = useRef<WebSocket | null>(null);

  useEffect(() => {
    const fetchBlockedUsers = async () => {
      try {
        const response = await fetch(`/blocked-users/${username}/`);
        const data = await response.json();
        setBlockedUsers(data.blockedUsers || []);
      } catch (error) {
        console.error("Failed to fetch blocked users:", error);
      }
    };

    fetchBlockedUsers();
  }, [username, onlineUsers]); // Re-fetch blocked users when online users change

  useEffect(() => {

    const wsUrl = `${wsBaseUrl}/ws/chat/?username=${username}`;
    ws.current = new WebSocket(wsUrl);

    ws.current.onopen = () => {
      console.log("WebSocket connected");
      console.log("Connected to the chat server.");
    };

    ws.current.onclose = () => {
      console.log("WebSocket disconnected");
      console.log("Disconnected from the chat server.");
    };

    ws.current.onmessage = (e) => {
      const data = JSON.parse(e.data);
      handleMessage(data);
    };

    return () => {
      ws.current?.close();
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  interface IncomingData {
    recipient: string | undefined;
    blocked_users: any;
    type: string;
    sender?: string;
    game_url?: string;
    message?: string;
    messages?: {
      recipient: any;
      is_dm: any;
      sender: string;
      text: string;
      is_announcement?: boolean;
    }[]; // Add messages here
    users?: string[];
    target_user?: string;
    url?: string;
  }

  const handleMessage = (data: IncomingData) => {
    switch (data.type) {
      case "game_invitation":
        if (data.sender && data.message) {
          addMessage({
            sender: data.sender,
            recipient: username,
            message: data.message, // Already formatted on the backend
            isDM: true,
            isAnnouncement: false,
          });
        }
        break;      
      case "update_users":
        if (data.users) {
          setOnlineUsers(data.users);
        }
        if (data.blocked_users) {
          setBlockedUsers(data.blocked_users);
        }
        break;
      case "chat_history":
        if (data.messages) {
          setMessages(
            data.messages.map((msg) => ({
              id: uuidv4(),
              sender: msg.sender,
              recipient: msg.recipient || "", // Ensure recipient is included
              message: msg.text,
              isDM: msg.is_dm,
              isAnnouncement: msg.is_announcement,
            }))
          );
        }
        break;
      case "chat":
        if (
          data.sender &&
          data.message &&
          !blockedUsers.includes(data.sender)
        ) {
          addMessage({
            sender: data.sender,
            message: data.message,
            isAnnouncement: false,
            recipient: "",
          });
        }
        break;
      case "direct":
        if (data.sender && data.message && data.recipient) {
          addMessage({
            sender: data.sender,
            recipient: data.recipient,
            message: data.message,
            isDM: true,
          });
        }
        break;
      case "error":
      case "block_success":
        setBlockedUsers((prev) => [...prev, data.target_user!]);
        console.log(data.message!);
        break;
      case "unblock_success":
        setBlockedUsers((prev) =>
          prev.filter((user) => user !== data.target_user)
        );
        console.log(data.message!);
        break;
      case "dm_sent":
        if (data.message) {
          console.log(data.message);
        }
        break;
      case "invite_game":
        if (data.target_user && data.url) {
          console.log(`Game invitation sent to '${data.target_user}'.`);
          window.open(data.url, "_blank");
        }
        break;
      case "announcement":
        if (data.sender && data.message) {
          addMessage({
            sender: data.sender,
            message: data.message,
            isAnnouncement: true,
            recipient: "",
          });
        }
        break;
      case "view_profile":
        if (data.url) {
          window.open(data.url, "_blank");
        }
        break;
      default:
        console.log("Unknown message type:", data.type);
    }
  };

  const addMessage = (msg: Omit<Message, "id">) => {
    setMessages((prev) => [...prev, { id: uuidv4(), ...msg }]);
  };

  const sendMessage = (message: string) => {
    if (message.length > 200) {
      console.log("Message too long. Maximum length is 200 characters.");
      return;
    }

    if (ws.current && ws.current.readyState === WebSocket.OPEN) {
      ws.current.send(JSON.stringify({ message }));
    } else {
      console.log("WebSocket is not connected.");
    }
  };

  const blockUser = (action: "block" | "unblock", user: string) => {
    if (ws.current && ws.current.readyState === WebSocket.OPEN) {
      ws.current.send(JSON.stringify({ command: action, target_user: user }));

      if (action === "block") {
        setBlockedUsers((prev) => [...prev, user]);
      } else {
        setBlockedUsers((prev) =>
          prev.filter((blockedUser) => blockedUser !== user)
        );

        // Fetch complete chat history after unblocking
        ws.current.send(
          JSON.stringify({
            command: "fetch_chat_history",
            include_blocked: true,
          })
        );
      }
    } else {
      console.log("WebSocket is not connected.");
    }
  };

  const sendDirectMessage = (recipient: string, message: string) => {
    if (ws.current && ws.current.readyState === WebSocket.OPEN) {
      const newMessage = {
        sender: username,
        recipient: recipient,
        message: message,
        isDM: true,
        isAnnouncement: false,
      };

      ws.current.send(JSON.stringify(newMessage));

      // Add the DM instantly to the local state
      setMessages((prevMessages) => [
        ...prevMessages,
        { ...newMessage, id: uuidv4() },
      ]);
    } else {
      console.log("WebSocket is not connected.");
    }
  };

  const inviteToGame = (target_user: string) => {
    const gameId = uuidv4(); // Generate a single shared game ID
    const inviterGameUrl = `/play/remote/${gameId}?key=${username}`; // URL for inviter
    const inviteeGameUrl = `/play/remote/${gameId}?key=${target_user}`; // URL for invitee
  
    // Navigate the inviter to the game in the same page
    window.location.href = inviterGameUrl;
  
    if (ws.current && ws.current.readyState === WebSocket.OPEN) {
      // Send the invite message with the invitee's URL
      ws.current.send(
        JSON.stringify({
          type: "invite_to_pong",
          target_user,
          game_id: gameId, // Shared game ID
          game_url: inviteeGameUrl, // Invitee's personalized URL
        })
      );
      console.log(`Game invitation sent to ${target_user}.`);
    } else {
      console.log("WebSocket is not connected.");
    }
  };  
  

  const viewProfile = (target_user: string) => {
    if (ws.current && ws.current.readyState === WebSocket.OPEN) {
      ws.current.send(JSON.stringify({ view_profile: true, target_user }));
    } else {
      console.log("WebSocket is not connected.");
    }
  };

  return (
    <>
      <div className="chat-page-container container-fluid">
        {/* Sidebar */}
        <div className="sidebar-container">
          <div className="card mb-3 profile-card sidebar-card">
            <div className="sidebar-header">
              <h4 className="profile-title text-white">Online Users</h4>
            </div>
            <div className="card-body profile-body sidebar-body-scroll">
              <OnlineUsers
                users={onlineUsers}
                currentUser={username}
                sendDirectMessage={sendDirectMessage}
                blockUser={blockUser}
                inviteToGame={inviteToGame}
                viewProfile={viewProfile}
                blockedUsers={blockedUsers} // Pass the blocked users
              />
            </div>
          </div>
        </div>

        {/* Main Chat Area */}
        <div className="main-chat-container ms-4">
          <div className="main-chat-header">
            <h4 className="profile-title text-white">Chat</h4>
          </div>
          <div className="card main-chat-card">
            <div className="main-chat-messages">
              <MessageList
                messages={messages}
                currentUser={username}
                blockedUsers={blockedUsers}
              />
            </div>
            <div className="main-chat-input">
              <MessageInput sendMessage={sendMessage} />
            </div>
          </div>
        </div>
      </div>
    </>
  );
};

export default Chat;
