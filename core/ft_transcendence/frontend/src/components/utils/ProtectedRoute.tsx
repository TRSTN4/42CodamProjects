import React, { useEffect, useState } from "react";
import { Navigate, Outlet } from "react-router-dom";
import { useAuth } from "./AuthContext";
import NavBar from "../NavBar";
import axiosInstance from "./AxiosInstance";
import SpinningLogo from "../SpinningLogo";

type ProtectedRouteProps = {
  userId: number;
};

const ProtectedRoute: React.FC<ProtectedRouteProps> = ({ userId }) => {
  const { isAuthenticated } = useAuth();

  const [user, setUser] = useState<string | null>(null);

  useEffect(() => {
    const fetchUser = async () => {
      try {
        const response = await axiosInstance.get(`/users/${userId}/`);
        setUser(response.data.username);
      } catch (error) {
        // console.error("Failed to fetch user data", error);
      }
    };

    fetchUser();
  }, [userId]);

  if (!user) return <SpinningLogo />;

  return isAuthenticated ? (
    <>
      <NavBar username={user} />
      <Outlet />
    </>
  ) : (
    <Navigate to="/" />
  );
};

export default ProtectedRoute;
