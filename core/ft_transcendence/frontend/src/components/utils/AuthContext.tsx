import React, {
  createContext,
  useState,
  useEffect,
  useContext,
  ReactNode,
} from "react";
import axios from "./AxiosInstance";
const wsBaseUrl = import.meta.env.VITE_WS_BASE_URL;

interface AuthContextType {
  isAuthenticated: boolean;
  userId: number;
  login: (token: string) => void;
  logout: () => void;
  setUserId: (id: number) => void;
  isAuthChecked: boolean;
  socket: WebSocket | null;
}

interface AuthProviderProps {
  children: ReactNode;
}

const AuthContext = createContext<AuthContextType | undefined>(undefined);

export const AuthProvider: React.FC<AuthProviderProps> = ({ children }) => {

  const [isAuthenticated, setIsAuthenticated] = useState<boolean>(false);
  const [userId, setUserId] = useState<number>(-1);
  const [isAuthChecked, setIsAuthChecked] = useState(false);
  const [socket, setSocket] = useState<WebSocket | null>(null);

  const socketUrl = `${wsBaseUrl}/ws/online_status/`;

  useEffect(() => {
    const checkAuthStatus = async () => {
      try {
        const response = await axios.get("users/auth/verify/");
        if (response.status === 200) {
          setIsAuthenticated(true);

          const userResponse = await axios.get("users/me/");
          if (userResponse.status === 200) {
            console.info("User authenticated:", userResponse);
            console.info("Setting user ID to:", userResponse.data.user_id);
            setUserId(userResponse.data.user_id);

            // Connect WebSocket with username in query
            connectSocket(userResponse.data.username);
          }
        }
      } catch (error) {
        setIsAuthenticated(false);
        setUserId(-1);
      } finally {
        setIsAuthChecked(true); // Mark auth check as complete
      }
    };

    checkAuthStatus();

    // Cleanup WebSocket on unmount
    return () => {
      if (socket) {
        console.log("Closing WebSocket connection...");
        socket.close();
      }
    };
  }, []);

  const connectSocket = (username: string) => {
    if (username) {
      console.log(`Connecting WebSocket with username: ${username}`);
      const ws = new WebSocket(`${socketUrl}?username=${username}`);

      ws.onopen = () => {
        console.log("WebSocket connected");
      };

      ws.onmessage = (event) => {
        console.log("Message received:", event.data);
      };

      ws.onclose = () => {
        console.warn("WebSocket closed");
        setSocket(null);
      };

      ws.onerror = (error) => {
        console.error("WebSocket error:", error);
        ws.close();
      };

      setSocket(ws);
    }
  };

  const login = (token: string) => {
    setIsAuthenticated(true);
    console.info("Login successful and token set:", token);
    // The server should handle setting cookies during login
  };

  const logout = async () => {
    try {
      const response = await axios.delete("users/auth/logout/");
      if (response.status === 200) {
        setIsAuthenticated(false);
        setUserId(-1);

        // Close WebSocket on logout
        if (socket) {
          console.log("Closing WebSocket connection on logout...");
          socket.close();
        }
      }
      console.log("Logout successful");
    } catch (error) {
      console.error("Logout failed:", error);
    }
  };

  return (
    <AuthContext.Provider
      value={{
        isAuthenticated,
        userId,
        login,
        logout,
        setUserId,
        isAuthChecked,
        socket,
      }}
    >
      {children}
    </AuthContext.Provider>
  );
};

export const useAuth = () => {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error("useAuth must be used within an AuthProvider");
  }
  return context;
};
