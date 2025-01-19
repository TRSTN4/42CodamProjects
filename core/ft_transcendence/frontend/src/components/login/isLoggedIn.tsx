import { useEffect } from "react";
import { useNavigate } from "react-router-dom";

export const IsLoggedIn = (userId: number, isAuthChecked: boolean) => {
  const navigate = useNavigate();

  useEffect(() => {
    if (isAuthChecked && userId !== -1) {
      navigate("/");
    }
  }, [userId, isAuthChecked, navigate]);
};
