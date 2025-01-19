import React from "react";
import { useNavigate } from "react-router-dom";
import "../css/UserProfile.css";

const NotFoundPage: React.FC = () => {
  const navigate = useNavigate();

  const handleGoHome = () => {
    navigate("/"); // Navigate to the home page or any specific route
  };

  return (
    <div className="container d-flex align-items-center justify-content-center vh-100">
      <div className="card profile-card mx-auto">
        <div className="card-header profile-header text-center">
          <h4 className="profile-title text-white">404 - Not Found</h4>
        </div>
        <div className="card-body profile-body text-center">
          <p className="mb-4">
            Oops! The page you're looking for doesn't exist.
          </p>
          <button className="btn btn-primary" onClick={handleGoHome}>
            Go to Home
          </button>
        </div>
        <div className="card-footer text-center">
          <p className="small">
            Need help? <a href="/contact">Contact Us</a>
          </p>
        </div>
      </div>
    </div>
  );
};

export default NotFoundPage;
