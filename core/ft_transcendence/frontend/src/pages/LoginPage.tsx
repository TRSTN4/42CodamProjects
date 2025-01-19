import React, { useState } from "react";
import { useAuth } from "../components/utils/AuthContext";
import { Link, useNavigate } from "react-router-dom";
import OTPBoxed from "../components/users/OTPBoxed";
import "../css/UserProfile.css";
import "../css/Utils.css";
import axiosInstance from "../components/utils/AxiosInstance";
import { IsLoggedIn } from "../components/login/isLoggedIn";
const apiBaseUrl = import.meta.env.VITE_API_BASE_URL;

type UserProfileProps = {
  userId: number;
  isAuthChecked: boolean;
};

const LoginPage: React.FC<UserProfileProps> = ({ userId, isAuthChecked }) => {
  IsLoggedIn(userId, isAuthChecked);
  const { login } = useAuth();
  const { setUserId } = useAuth();
  const navigate = useNavigate();

  const [formData, setFormData] = useState({
    username: "",
    password: "",
  });

  const [formErrors, setFormErrors] = useState({
    username: "",
    password: "",
  });

  const [isOtpSent, setIsOtpSent] = useState(false);
  const [otpUserEmail, setOtpUserEmail] = useState<string | null>(null);
  const [alertMessage, setAlertMessage] = useState<string | null>(null);
  const [alertType, setAlertType] = useState<"success" | "error" | null>(null);

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;
    setFormData({ ...formData, [name]: value });

    // Validation logic
    if (name === "username") {
      setFormErrors({
        ...formErrors,
        username: value.trim() === "" ? "Username is required" : "",
      });
    }

    if (name === "password") {
      setFormErrors({
        ...formErrors,
        password: value.trim() === "" ? "Password is required" : "",
      });
    }
  };

  const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();

	const errors: { [key: string]: string } = {};
	if (!formData.username) errors.username = "Username is required";
	if (!formData.password) errors.password = "Password is required";
	
	setFormErrors({ ...formErrors, ...errors });
	if (Object.keys(errors).length > 0){
		setAlertMessage("Please fix the errors before submitting.");
		setAlertType("error");
		return;
	}
    if (
      formErrors.username ||
      formErrors.password ||
      !formData.username ||
      !formData.password
    ) {
      setAlertMessage("Please fix the errors before submitting.");
      setAlertType("error");
      return;
    }

    try {
      const config = {
        headers: {
          "Content-Type": "application/json",
        },
      };

      const response = await axiosInstance.post(
        "/users/login/",
        formData,
        config
      );
      console.warn("RESPONSE HEADER AFTER LOGIN:", response);
      if (response.status === 200 && response.data?.user_id) {
        login(response.data.acces_token);
        setUserId(response.data.user_id);
        setAlertMessage("Login successful!");
        setAlertType("success");
        setTimeout(() => navigate("/"), 500);
      } else if (response.status === 202 && response.data?.email) {
        const userEmail = response.data.email;
        setOtpUserEmail(userEmail);
        setIsOtpSent(true);
        setAlertMessage("OTP sent to your email.");
        setAlertType("success");
      } else {
        setAlertMessage("Unexpected response from the server.");
        setAlertType("error");
      }
    } catch (error) {
      console.error("Error during login:", error);
      setAlertMessage("Invalid username or password.");
      setAlertType("error");
    }
  };

  const handleAuthentication = () => {
    window.location.href = `${apiBaseUrl}/users/42_login/`;
  };

  return (
    <div className="container d-flex align-items-center justify-content-center vh-100">
      {!isOtpSent ? (
        <div className="card profile-card mx-auto">
          <div className="card-header profile-header text-center">
            <h4 className="profile-title text-white">Login</h4>
          </div>
          <div className="card-body">
            {/* Alert Box */}
            {alertMessage && (
              <div
                className={`alert ${
                  alertType === "success" ? "alert-success" : "alert-danger"
                } text-center`}
              >
                {alertMessage}
              </div>
            )}

            <form onSubmit={handleSubmit} noValidate>
              <div>
                <button
                  onClick={handleAuthentication}
                  type="button"
                  className="btn login-button"
                >
                  Login with <img src="/42.png" alt="42" className="logo-42" />
                </button>
              </div>
              <div className="form-group">
                <label htmlFor="username"></label>
                <div className="input-group mb-3">
                  <div className="input-group-prepend">
                    <span className="input-group-text">@</span>
                  </div>
                  <input
                    type="text"
                    className={`form-control ${
                      formErrors.username ? "is-invalid" : ""
                    }`}
                    id="username"
                    name="username"
                    placeholder="Username"
                    value={formData.username}
                    onChange={handleChange}
                    required
                  />
                  {formErrors.username && (
                    <div className="invalid-feedback">
                      {formErrors.username}
                    </div>
                  )}
                </div>
              </div>

              <div className="form-group">
                <label htmlFor="password"></label>
                <input
                  type="password"
                  className={`form-control ${
                    formErrors.password ? "is-invalid" : ""
                  }`}
                  id="password"
                  name="password"
                  placeholder="Password"
                  value={formData.password}
                  onChange={handleChange}
                  required
                />
                {formErrors.password && (
                  <div className="invalid-feedback">{formErrors.password}</div>
                )}
              </div>
              <div className="d-flex flex-column align-items-center">
                <button type="submit" className="btn btn-primary mt-3">
                  Login
                </button>
              </div>
            </form>
          </div>
          <div className="card-footer text-center">
            <p className="small">
              Don't have an account? <Link to="/register">Register</Link>
            </p>
          </div>
        </div>
      ) : (
        otpUserEmail !== null && <OTPBoxed email={otpUserEmail} />
      )}
    </div>
  );
};

export default LoginPage;
