import React, { useState } from "react";
import axiosInstance from "../utils/AxiosInstance";
import axios from "axios";
import "../../css/UserProfile.css";
import ChangeAvatar from "./ChangeAvatar";
import ChangePassword from "./ChangePassword";
import { useNavigate } from "react-router-dom";

interface ChangeDetailsProps {
  username: string;
  firstName: string;
  email: string;
  twoFactorEnabled: boolean;
  avatarUrl: string;
  userId: number;
}

const ChangeDetails: React.FC<ChangeDetailsProps> = ({
  username,
  firstName,
  email,
  twoFactorEnabled,
  avatarUrl,
  userId,
}) => {
  const [formData, setFormData] = useState({
    username,
    firstName,
    email,
    twoFactorEnabled,
  });

  const [formErrors, setFormErrors] = useState({
    username: "",
    email: "",
    firstName: "",
  });

  const [isEditingAvatar, setIsEditingAvatar] = useState(false);
  const [isChangingPassword, setIsChangingPassword] = useState(false);
  const [alertMessage, setAlertMessage] = useState<string | null>(null);
  const [alertType, setAlertType] = useState<"success" | "error" | null>(null);

  const navigate = useNavigate();

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;
    setFormData({ ...formData, [name]: value });
    if (name === "username") {
      const usernameRegex = /^[a-zA-Z0-9-]{1,20}$/;
      setFormErrors({
        ...formErrors,
        username: usernameRegex.test(value)
          ? ""
          : "Username must be max 20 characters, alphanumeric or '-' only",
      });
    }

    if (name === "email") {
      const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
      setFormErrors({
        ...formErrors,
        email: emailRegex.test(value) ? "" : "Invalid email address",
      });
    }

    if (name === "firstName") {
      const firstNameRegex = /^[a-zA-Z]{1,15}$/;
      setFormErrors({
        ...formErrors,
        firstName: firstNameRegex.test(value)
          ? ""
          : "First name must only contain letters and be no longer than 15 characters",
      });
    }
  };

  const handleCheckboxChange = () => {
    setFormData({ ...formData, twoFactorEnabled: !formData.twoFactorEnabled });
  };

  const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    if (
      formErrors.username ||
      formErrors.email ||
      !formData.username ||
      !formData.email
    ) {
      console.log("Please fix the errors before submitting.");
      return;
    }

    try {
      const response = await axiosInstance.patch(
        `/users/${userId}/`,
        formData,
        {
          headers: { "Content-Type": "application/json" },
        }
      );
      if (response.status === 200) {
		setAlertMessage("Details updated successfully.");
		setAlertType("success");
        navigate(`/users/${formData.username}`);
      }
    } catch (error) {
		console.error("Error submitting form:", error);
	  
		if (axios.isAxiosError(error)) {
		  if (error.response && error.response.data) {
			const responseData = error.response.data;
	  
			// Check for specific fields: email and username
			if (responseData.email) {
			  setAlertMessage(`Email: ${responseData.email.join(", ")}`);
			} else if (responseData.username) {
			  setAlertMessage(`Username: ${responseData.username.join(", ")}`);
			} else {
			  setAlertMessage("An unknown error occurred.");
			}
		  } else if (error.request) {
			setAlertMessage("No response from the server.");
		  } else {
			setAlertMessage("An unexpected error occurred.");
		  }
		} else {
		  setAlertMessage("An unknown error occurred.");
		}
		setAlertType("error");
	  }
  };

  const handleCancel = () => {
    navigate(`/users/${username}`);
  };

  return (
    <div className="container d-flex align-items-center justify-content-center">
      {isEditingAvatar && (
        <div className="popup-overlay">
          <div className="popup-content">
            <ChangeAvatar
              avatarUrl={avatarUrl}
              userId={userId}
              username={username}
              onClose={() => setIsEditingAvatar(false)}
            />
          </div>
        </div>
      )}
      {isChangingPassword && (
        <div className="popup-overlay">
          <div className="popup-content">
            <ChangePassword
              userId={userId}
              username={username}
              onClose={() => setIsChangingPassword(false)}
            />
          </div>
        </div>
      )}
      <div className="card profile-card mt-4">
        <div className="profile-header d-flex flex-column align-items-center p-3">
          <img
            src={avatarUrl}
            alt="Avatar"
            className="rounded-circle"
            style={{ width: "100px", height: "100px", objectFit: "cover" }}
          />
          <button
            className="btn btn-primary mt-3"
            onClick={() => setIsEditingAvatar(true)}
          >
            Edit
          </button>
        </div>
        <div className="profile-body p-4">
		{alertMessage && (
              <div
                className={`alert ${
                  alertType === "success" ? "alert-success" : "alert-danger"
                } text-center`}
              >
                {alertMessage}
              </div>
            )}
          <h2 className="profile-title mb-4">Change Details</h2>
          <form onSubmit={handleSubmit}>
            <div className="d-flex flex-column mb-3">
              <label htmlFor="username" className="form-label">
                Username
              </label>
              <input
                type="text"
                className={`form-control ${
                  formErrors.username ? "is-invalid" : ""
                }`}
                id="username"
                name="username"
                value={formData.username}
                onChange={handleChange}
              />
            </div>
            <div className="d-flex flex-column mb-3">
              <label htmlFor="firstName" className="form-label">
                First Name
              </label>
              <input
                type="text"
                className={`form-control ${
                  formErrors.firstName ? "is-invalid" : ""
                }`}
                id="firstName"
                name="firstName"
                value={formData.firstName}
                onChange={handleChange}
              />
              {formErrors.firstName && (
                <div className="invalid-feedback">{formErrors.firstName}</div>
              )}
            </div>
            <div className="d-flex flex-column mb-3">
              <label htmlFor="email" className="form-label">
                Email
              </label>
              <input
                type="email"
                className={`form-control ${
                  formErrors.email ? "is-invalid" : ""
                }`}
                id="email"
                name="email"
                value={formData.email}
                onChange={handleChange}
              />
              {formErrors.email && (
                <div className="invalid-feedback">{formErrors.email}</div>
              )}
            </div>
            <div className="d-flex justify-content-center mb-3 form-check form-switch custom-form-switch">
              <input
                type="checkbox"
                className="form-check-input"
                id="twoFactorEnabled"
                checked={formData.twoFactorEnabled}
                onChange={handleCheckboxChange}
              />
              <label
                className="form-check-label ms-4"
                htmlFor="twoFactorEnabled"
              >
                Enable Two-Factor Authentication
              </label>
            </div>
            <div className="d-flex justify-content-between mt-4">
              <button
                type="button"
                className="btn btn-primary"
                onClick={() => setIsChangingPassword(true)}
              >
                Change Password
              </button>
              <div>
                <button
                  type="button"
                  className="btn btn-danger"
                  onClick={handleCancel}
                >
                  Cancel
                </button>
                <button type="submit" className="btn btn-success ms-2">
                  Save
                </button>
              </div>
            </div>
          </form>
        </div>
      </div>
    </div>
  );
};

export default ChangeDetails;
