import { useEffect } from "react";
import { useNavigate } from "react-router-dom";

export const NotLoggedIn = (userId: number, isAuthChecked: boolean) => {
  const navigate = useNavigate();

  useEffect(() => {
    if (isAuthChecked && userId === -1) {
      navigate("/hello");
    }
  }, [userId, isAuthChecked, navigate]);
};
