// src/components/Notifications.tsx

import React from "react";

interface NotificationItem {
  id: string;
  message: string;
}

interface NotificationsProps {
  notifications: NotificationItem[];
}

const Notifications: React.FC<NotificationsProps> = ({ notifications }) => {
  return (
    <div className="notification-container">
      {notifications.map((note) => (
        <div className="notification" key={note.id}>
          {note.message}
        </div>
      ))}
    </div>
  );
};

export default Notifications;
