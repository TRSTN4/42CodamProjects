import React, { useState } from "react";
import axiosInstance from "../utils/AxiosInstance";
import { useNavigate } from "react-router-dom";

interface ChangePasswordProps {
  userId: number;
  username: string;
  onClose: () => void;
}

const ChangePassword: React.FC<ChangePasswordProps> = ({
  userId,
  username,
  onClose,
}) => {
  const [password, setPassword] = useState("");
  const [confirmPassword, setConfirmPassword] = useState("");
  const [formErrors, setFormErrors] = useState({
    password: "",
    confirmPassword: "",
  });
  const [isLoading, setIsLoading] = useState(false);
  const [alertMessage, setAlertMessage] = useState<string | null>(null);
  const navigate = useNavigate();

  const validatePassword = (password: string) => {
    const passwordRegex =
      /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/;
    return passwordRegex.test(password)
      ? ""
      : "Password must be at least 8 characters long, include an uppercase letter, a lowercase letter, a number, and a special character.";
  };

  const handlePasswordChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { value } = e.target;
    setPassword(value);
    setFormErrors({
      ...formErrors,
      password: validatePassword(value),
    });
  };

  const handleConfirmPasswordChange = (
    e: React.ChangeEvent<HTMLInputElement>
  ) => {
    const { value } = e.target;
    setConfirmPassword(value);
    setFormErrors({
      ...formErrors,
      confirmPassword: value !== password ? "Passwords do not match." : "",
    });
  };

  const handleSubmit = async () => {
    if (formErrors.password || formErrors.confirmPassword || !password) {
      setAlertMessage("Please fix the errors before submitting.");
      return;
    }

    setIsLoading(true);

    try {
      const response = await axiosInstance.patch(
        `/users/${userId}/`,
        { password },
        {
          headers: {
            "Content-Type": "application/json",
          },
        }
      );

      if (response.status === 200) {
        setAlertMessage("Password changed successfully!");
        setTimeout(() => navigate(`/users/${username}`), 1000);
      }
    } catch (error) {
      console.error("Error changing password:", error);
      setAlertMessage("Failed to change password. Please try again.");
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div className="change-password-modal">
      <div className="modal-content">
        <h2 className="profile-title">Change Password</h2>
        {alertMessage && (
          <div
            className={`alert ${
              alertMessage.includes("success")
                ? "alert-success"
                : "alert-danger"
            } text-center`}
          >
            {alertMessage}
          </div>
        )}
        <div className="d-flex flex-column form-group mt-4">
          <label htmlFor="password" className="form-label">
            New Password
          </label>
          <input
            type="password"
            id="password"
            className={`form-control ${
              formErrors.password ? "is-invalid" : ""
            }`}
            value={password}
            onChange={handlePasswordChange}
            required
          />
          {formErrors.password && (
            <div className="invalid-feedback">{formErrors.password}</div>
          )}
        </div>
        <div className="d-flex flex-column form-group mt-3">
          <label htmlFor="confirmPassword" className="form-label">
            Confirm Password
          </label>
          <input
            type="password"
            id="confirmPassword"
            className={`form-control ${
              formErrors.confirmPassword ? "is-invalid" : ""
            }`}
            value={confirmPassword}
            onChange={handleConfirmPasswordChange}
            required
          />
          {formErrors.confirmPassword && (
            <div className="invalid-feedback">{formErrors.confirmPassword}</div>
          )}
        </div>
        <div className="modal-actions d-flex justify-content-between mt-4">
          <button
            className="btn btn-secondary"
            onClick={onClose}
            disabled={isLoading}
          >
            Cancel
          </button>
          <button
            className="btn btn-primary"
            onClick={handleSubmit}
            disabled={isLoading || !password || !confirmPassword}
          >
            {isLoading ? "Saving..." : "Save Password"}
          </button>
        </div>
      </div>
    </div>
  );
};

export default ChangePassword;
