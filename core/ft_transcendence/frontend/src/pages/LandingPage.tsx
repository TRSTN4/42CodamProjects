// LandingPage.tsx

import React from "react";
import { Link } from "react-router-dom";
import "../css/Utils.css";

const LandingPage: React.FC = () => {
  return (
    <div className="d-flex flex-column align-items-center justify-content-center vh-100">
      <h1 className="text-white fst-italic playfair-text mb-4">
        WELCOME TO PONG
      </h1>
      <div className="d-flex align-items-center">
        <Link to="/login">
          <button
            type="button"
            className="btn btn-primary glass-button-sc me-4"
          >
            Login
          </button>
        </Link>
        <Link to="/register">
          <button type="button" className="btn btn-primary glass-button">
            Register
          </button>
        </Link>
      </div>
    </div>
  );
};

export default LandingPage;
