import React, { useState } from "react";
import { useAuth } from "../components/utils/AuthContext";
import { Link, useNavigate } from "react-router-dom";
import OTPBoxed from "../components/users/OTPBoxed";
import axiosInstance from "../components/utils/AxiosInstance";
import { IsLoggedIn } from "../components/login/isLoggedIn";
import "../css/UserProfile.css";

type UserProfileProps = {
  userId: number;
  isAuthChecked: boolean;
};

const RegisterPage: React.FC<UserProfileProps> = ({
  userId,
  isAuthChecked,
}) => {
  IsLoggedIn(userId, isAuthChecked);
  const { setUserId } = useAuth();
  const navigate = useNavigate();

  const [formData, setFormData] = useState({
    username: "",
    firstName: "",
    email: "",
    password: "",
    confirmPassword: "",
    twoFactorEnabled: false,
  });

  const [formErrors, setFormErrors] = useState({
    username: "",
    email: "",
    password: "",
    confirmPassword: "",
    firstName: "",
  });

  const [isOtpSent, setIsOtpSent] = useState(false);
  const [otpUserEmail, setOtpUserEmail] = useState<string | null>(null);
  const [alertMessage, setAlertMessage] = useState<string | null>(null);
  const [alertType, setAlertType] = useState<"success" | "error" | null>(null);

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
	const { name, value, type, checked } = e.target;
	setFormData({
	  ...formData,
	  [name]: type === "checkbox" ? checked : value,
	});
  
	if (name === "username") {
	  const usernameRegex = /^[a-zA-Z0-9-]{1,20}$/; // Alphanumeric and '-' only, max 20 characters
	  setFormErrors({
		...formErrors,
		username: usernameRegex.test(value)
		  ? ""
		  : "Username must be max 20 characters, alphanumeric or '-' only",
	  });
	}
  
	if (name === "email") {
	  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/; // Valid email format
	  setFormErrors({
		...formErrors,
		email: emailRegex.test(value) ? "" : "Invalid email address",
	  });
	}
  
	if (name === "password") {
	  const passwordRegex =
		/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,30}$/;
	  setFormErrors({
		...formErrors,
		password: passwordRegex.test(value)
		  ? ""
		  : "Password must be 8-30 characters, include uppercase, lowercase, number, and a special character",
	  });
	}
  
	if (name === "confirmPassword") {
	  setFormErrors({
		...formErrors,
		confirmPassword:
		  value !== formData.password ? "Passwords do not match" : "",
	  });
	}
  
	if (name === "firstName") {
		const firstNameRegex = /^[a-zA-Z]{1,15}$/; // Only alphanumeric, max 15 chars
		setFormErrors({
		  ...formErrors,
		  firstName: firstNameRegex.test(value)
			? ""
			: "First name must only contain letters and be no longer than 15 characters",
		});
	  }
  };
  

  const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
	e.preventDefault();
  
	// Check for empty fields
	const errors: { [key: string]: string } = {};
	if (!formData.username) errors.username = "Username is required";
	if (!formData.firstName) errors.firstName = "First name is required";
	if (!formData.email) errors.email = "Email is required";
	if (!formData.password) errors.password = "Password is required";
	if (!formData.confirmPassword) {
	  errors.confirmPassword = "Confirm password is required";
	} else if (formData.password !== formData.confirmPassword) {
	  errors.confirmPassword = "Passwords do not match";
	}
  
	// Update form errors state
	setFormErrors({ ...formErrors, ...errors });
  
	// Stop submission if there are errors
	if (Object.keys(errors).length > 0) {
	  setAlertMessage("Please fix the errors before submitting.");
	  setAlertType("error");
	  return;
	}
  
	// Exclude confirmPassword from the data to be sent
	const { confirmPassword, ...dataToSend } = formData;
  
	const config = {
	  headers: {
		"Content-Type": "application/json",
	  },
	};
  
	try {
	  console.log(dataToSend);
	  const response = await axiosInstance.post(
		"/users/register/",
		dataToSend,
		config
	  );
	  console.info(response);
  
	  if (response.status === 200 && response.data?.user_id) {
		setUserId(response.data.user_id);
		setAlertMessage("Registration successful!");
		setAlertType("success");
		setTimeout(() => navigate("/"), 1000);
	  } else if (response.status === 202 && response.data?.email) {
		console.log(response.data.message);
		const userEmail = response.data.email;
		setAlertMessage("OTP sent to your email.");
		setAlertType("success");
		setOtpUserEmail(userEmail);
		setIsOtpSent(true);
	  }
	} catch (error) {
	  console.error("Error submitting form:", error);
	  setAlertMessage("Failed to register. Please try again.");
	  setAlertType("error");
	}
  };
  

  return (
    <div className="container d-flex align-items-center justify-content-center vh-100">
      {!isOtpSent ? (
        <div className="card profile-card mx-auto">
          <div className="card-header profile-header text-center">
            <h4 className="profile-title text-white">Register</h4>
          </div>
          <div className="card-body profile-body">
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
              <div className="form-group">
                <label htmlFor="username"></label>
                <div className="input-group">
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
                <label htmlFor="firstName"></label>
                <input
                  type="text"
                  className={`form-control ${
                    formErrors.firstName ? "is-invalid" : ""
                  }`}
                  id="firstName"
                  name="firstName"
                  placeholder="First Name"
                  value={formData.firstName}
                  onChange={handleChange}
                  required
                />
                {formErrors.firstName && (
                  <div className="invalid-feedback">{formErrors.firstName}</div>
                )}
              </div>
              <div className="form-group">
                <label htmlFor="email"></label>
                <input
                  type="email"
                  className={`form-control ${
                    formErrors.email ? "is-invalid" : ""
                  }`}
                  id="email"
                  name="email"
                  placeholder="Email"
                  value={formData.email}
                  onChange={handleChange}
                  required
                />
                {formErrors.email && (
                  <div className="invalid-feedback">{formErrors.email}</div>
                )}
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

              <div className="form-group">
                <label htmlFor="confirmPassword"></label>
                <input
                  type="password"
                  className={`form-control ${
                    formErrors.confirmPassword ? "is-invalid" : ""
                  }`}
                  id="confirmPassword"
                  name="confirmPassword"
                  placeholder="Confirm Password"
                  value={formData.confirmPassword}
                  onChange={handleChange}
                  required
                />
                {formErrors.confirmPassword && (
                  <div className="invalid-feedback">
                    {formErrors.confirmPassword}
                  </div>
                )}
              </div>

              <div className="d-flex mt-3 justify-content-center">
                <input
                  type="checkbox"
                  className="form-check-input checkmark"
                  id="twoFactorEnabled"
                  name="twoFactorEnabled"
                  checked={formData.twoFactorEnabled}
                  onChange={handleChange}
                />
                <label
                  className="form-check-label ps-2 text-secondary"
                  htmlFor="twoFactorEnabled"
                >
                  Enable 2FA
                </label>
              </div>

              <button type="submit" className="btn btn-primary btn-block mt-3">
                Register
              </button>
            </form>
          </div>
          <div className="card-footer text-center">
            <p className="small">
              Already have an account? <Link to="/login">Login</Link>
            </p>
          </div>
        </div>
      ) : (
        otpUserEmail !== null && <OTPBoxed email={otpUserEmail} />
      )}
    </div>
  );
};

export default RegisterPage;
