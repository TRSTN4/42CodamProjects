import React, { useEffect } from "react";
import { useNavigate } from "react-router-dom";
import "../css/SpinningLogo.css";
import "../css/UserProfile.css";

const SpinningLogo: React.FC = () => {
  const navigate = useNavigate();

  useEffect(() => {
    const timeoutId = setTimeout(() => {
      navigate("/");
    }, 5000);

    // Cleanup if the component unmounts before the timeout completes
    return () => {
      clearTimeout(timeoutId);
    };
  }, [navigate]);

  return (
    <div className="container d-flex flex-column align-items-center justify-content-center">
      <div className="card profile-card mx-auto">
        <div className="card-header profile-header text-center">
          <h4 className="profile-title text-white">Loading... </h4>
        </div>
        <div className="card-body profile-body d-flex justify-content-center main-con">
          {/* <div className="spinner"></div> */}
          {/* <div className="loader"></div> */}
          {/* <div className="ping"></div> */}
          <section className="dots-container">
            <div className="dot"></div>
            <div className="dot"></div>
            <div className="dot"></div>
            <div className="dot"></div>
            <div className="dot"></div>
          </section>
        </div>
      </div>
    </div>
  );
};

export default SpinningLogo;
