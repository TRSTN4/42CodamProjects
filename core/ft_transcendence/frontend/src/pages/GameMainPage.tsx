import React from "react";
import { Link } from "react-router-dom";
import "../css/UserProfile.css";

const GameMainPage: React.FC = () => {
  return (
    <div className="d-flex flex-column align-items-center justify-content-center vh-100">
      <div>
        <h1 className="text-white fst-italic playfair-text mb-4">
          START A GAME
        </h1>
      </div>
      <div>
        <Link to="/play/remote">
          <button className="btn btn-primary glass-button">Remote Play</button>
        </Link>
        <Link to="/play/local" style={{ marginLeft: "10px" }}>
          <button className="btn btn-primary glass-button">Local Play</button>
        </Link>
        <Link to="/play/tournaments" style={{ marginLeft: "10px" }}>
          <button className="btn btn-primary glass-button">Tournaments</button>
        </Link>
      </div>
    </div>
  );
};

export default GameMainPage;
