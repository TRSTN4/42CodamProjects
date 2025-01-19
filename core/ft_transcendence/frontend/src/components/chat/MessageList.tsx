import React, { useEffect, useRef } from "react";
import "../../css/chat/MessageList.css";

interface Message {
  recipient: string;
  id: string;
  sender: string;
  message: string;
  isDM?: boolean;
  isAnnouncement?: boolean;
}

interface MessageListProps {
  messages: Message[];
  currentUser: string;
  blockedUsers: string[];
}

const MessageList: React.FC<MessageListProps> = ({
  messages,
  currentUser,
  blockedUsers,
}) => {
  const endOfMessagesRef = useRef<HTMLDivElement | null>(null);

  const scrollToBottom = () => {
    if (endOfMessagesRef.current) {
      endOfMessagesRef.current.scrollIntoView({ behavior: "smooth" });
    }
  };

  useEffect(() => {
    scrollToBottom();
  }, [messages]);

  const filteredMessages = messages.filter(
    (msg) =>
      !blockedUsers.includes(msg.sender) &&
      (!msg.isDM || msg.sender === currentUser || msg.recipient === currentUser)
  );

  const renderMessageContent = (message: string) => {
    return <span dangerouslySetInnerHTML={{ __html: message }} />;
  };
  
  return (
    <div className="list-container">
      {filteredMessages.map((msg) => {
        const isOwn = msg.sender === currentUser;
        const bubbleClass = msg.message.includes("invited you to a match")
          ? "game-invitation-bubble"
          : msg.isAnnouncement
          ? "announcement-bubble"
          : isOwn
          ? "message-own"
          : "message-other";

        const senderText = msg.message.includes("invited you to a match")
          ? `${msg.sender}`
          : msg.isAnnouncement
          ? "Server Announcement"
          : msg.isDM
          ? `DM ${isOwn ? "to" : "from"} ${isOwn ? msg.recipient : msg.sender}`
          : msg.sender;

        return (
          <div key={msg.id} className="message-item-container">
            <div className={`message-bubble ${bubbleClass}`}>
              {renderMessageContent(msg.message)}
            </div>
            {!msg.isAnnouncement && (
              <div className={isOwn ? "sender-own" : "sender-other"}>
                {senderText}
              </div>
            )}
          </div>
        );
      })}
      <div ref={endOfMessagesRef} />
    </div>
  );
};

export default MessageList;
