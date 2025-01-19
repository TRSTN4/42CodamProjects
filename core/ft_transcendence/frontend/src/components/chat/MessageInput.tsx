// src/components/MessageInput.tsx

import React, { useState, FormEvent, ChangeEvent } from "react";
import "../../css/chat/MessageInput.css";

interface MessageInputProps {
  sendMessage: (message: string) => void;
}

const MessageInput: React.FC<MessageInputProps> = ({ sendMessage }) => {
  const [message, setMessage] = useState("");
  const [charCount, setCharCount] = useState(0);

  const handleSubmit = (e: FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    if (message.trim() !== "") {
      sendMessage(message);
      setMessage("");
      setCharCount(0);
    }
  };

  const handleChange = (e: ChangeEvent<HTMLInputElement>) => {
    const value = e.target.value;
    setMessage(value);
    setCharCount(value.length);
  };

  return (
    <form className="input-container" onSubmit={handleSubmit}>
      <input
        className="message-input"
        type="text"
        placeholder="Type your message..."
        value={message}
        onChange={handleChange}
        maxLength={200}
        required
      />
      <small>{charCount}/200</small>
      <button className="btn btn-primary send-button" type="submit">
        Send
      </button>
    </form>
  );
};

export default MessageInput;
