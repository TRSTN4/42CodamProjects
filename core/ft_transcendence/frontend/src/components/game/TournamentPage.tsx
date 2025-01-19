import React, { useEffect, useState } from "react";
import "../../css/game/TournamentPage.css";
import "../../css/UserProfile.css";
import axiosInstance from "../utils/AxiosInstance";
import { Link } from "react-router-dom";
const wsBaseUrl = import.meta.env.VITE_WS_BASE_URL;

// Example: your match interface might also have `in_progress?: boolean;`
interface Match {
  id: number;
  players: string[];
  winner: string | null;
  game_id?: string;
  in_progress?: boolean; // If your backend sets this when someone joins
  connected_count?: number;
}

interface FinalResult {
  type: "winner" | "draw";
  usernames: string[];
}

interface Tournament {
  organizer: string;
  players: string[]; // List of user *identifiers* (ex: real usernames)
  display_names?: {
    // If storing display names in the tournament
    [username: string]: string;
  };
  timer: number | null;
  is_started: boolean;
  matches: Match[];
  final_result?: FinalResult | null;
}

const TournamentPage: React.FC = () => {
  const [tournament, setTournament] = useState<Tournament | null>(null);
  const [username, setUsername] = useState("");
  const [displayName, setDisplayName] = useState(""); // local state for user’s unique name input
  
  useEffect(() => {
    fetchTournament();
    fetchUsername();

    // Subscribe to your "tournament_updates" WebSocket
    const socket = new WebSocket(`${wsBaseUrl}/ws/tournament/`);
    socket.onmessage = (event) => {
      const data = JSON.parse(event.data);
      // If data has "timer" => it's your tournament info, else null
      setTournament(data.timer !== undefined ? data : null);
    };
    return () => {
      socket.close();
    };
  }, []);

  const fetchTournament = async () => {
    try {
      const response = await axiosInstance.get("/api/tournament/");
      setTournament(response.data);
    } catch (error) {
      console.error("No active tournament found:", error);
    }
  };

  const fetchUsername = async () => {
    try {
      const response = await axiosInstance.get("/api/user/me/");
      const user = response.data?.username;
      if (!user) throw new Error("Username not found in response.");
      setUsername(user);
    } catch (error) {
      console.error("Failed to fetch username:", error);
      setUsername("");
    }

	const interval = setInterval(() => {
		refreshTournament();
	}, 5000);
	return () => clearInterval(interval);
  };

  /**
   * Toggles sign-in or sign-out of the tournament.
   * If user is currently signed out, we send { display_name } to the server.
   * If user is already signed in, we just call the endpoint with no display_name to sign out.
   */
  const toggleSignIn = async () => {
    if (!tournament) return;

    const isSignedIn = tournament.players.includes(username);

    // If user is not signed in, we require a displayName
    if (!isSignedIn) {
      if (!displayName.trim()) {
        alert("Please enter a unique display name before signing in.");
        return;
      }
      try {
        await axiosInstance.post("/api/tournament/sign-in/", {
          display_name: displayName,
        });
        // Clear local input (optional)
        setDisplayName("");
      } catch (error) {
        console.error("Failed to sign in:", error);
      }
    } else {
      // If user is already signed in, this toggles to sign-out
      try {
        await axiosInstance.post("/api/tournament/sign-in/");
      } catch (error) {
        console.error("Failed to sign out:", error);
      }
    }
  };

  const handlePlayMatch = async (matchId: number) => {
    try {
      // Hit your "assign-game" endpoint or "play-match" endpoint
      const response = await axiosInstance.post("/api/assign-game/", {
        match_id: matchId,
      });
      const { game_id } = response.data;
      window.location.href = `/play/remote/${game_id}?key=${username}`;
    } catch (error) {
      console.error("Failed to assign game to match:", error);
    }
  };

  const handleCloseTournament = async () => {
    try {
      await axiosInstance.post("/api/tournament/close/");
    } catch (error) {
      console.error("Failed to close tournament:", error);
    }
  };

  const isSignedIn = tournament && tournament.players.includes(username);
  const isOrganizer = tournament && tournament.organizer === username;

  const renderFinalResult = () => {
    if (!tournament || !tournament.final_result) return null;
    const { type, usernames } = tournament.final_result;
    const displayUsernames = usernames.map(
      (uname) => tournament.display_names?.[uname] || uname
    );

    if (type === "winner") {
      return <h2>Winner: {displayUsernames.join(", ")}</h2>;
    } else if (type === "draw") {
      return <h2>Draw: {displayUsernames.join(", ")}</h2>;
    }
    return null;
  };

  const refreshTournament = () => {
	fetchTournament();
  };

  return (
    <div className="container d-flex flex-column align-items-center justify-content-center">
      <div className="card profile-card mx-auto">
        <div className="card-header profile-header text-center">
          <h1 className="profile-title text-white">Tournament</h1>
        </div>
        <div className="card-body profile-body">
          {/* If no tournament, show create button */}
          {!tournament ? (
            <div className="create-tournament d-flex flex-column align-items-center justify-content-center">
              <h3 className="profile-title">No active tournament</h3>
              <button
                className="btn btn-primary"
                onClick={() => axiosInstance.post("/api/tournament/create/")}
              >
                Create Tournament
              </button>
            </div>
          ) : (
            <>
              {/* Basic Info */}
              <h3>
                <strong>Tournament organized by: </strong>
                {tournament.display_names?.[tournament.organizer] ||
                  tournament.organizer}{" "}
              </h3>
              <p>
                Players ({tournament.players.length}):{" "}
                {tournament.players
                  .map((uname) => tournament.display_names?.[uname] || uname)
                  .join(", ") || "None"}
              </p>
              {tournament.timer !== null && !tournament.is_started && (
                <p>Starting in: {tournament.timer}s</p>
              )}

              {/* If final results exist, show them */}
              {renderFinalResult()}

              {/* DisplayName input & sign-in/out */}
              {!tournament.is_started && (
                <div className="d-flex align-items-center justify-content-center">
                  {!isSignedIn && (
                    <input
                      type="text"
                      placeholder="Enter unique display name"
                      className="form-control input-display-name"
                      value={displayName}
                      onChange={(e) => setDisplayName(e.target.value)}
                      style={{ marginRight: "8px" }}
                    />
                  )}

                  <button className="btn btn-primary" onClick={toggleSignIn}>
                    {isSignedIn ? "Leave Tournament" : "Enter Tournament"}
                  </button>
                </div>
              )}

              {/* List matches once tournament is started but no final result */}
              {tournament.is_started && !tournament.final_result && (
                <div className="matches-container">
                  <h3>Matches</h3>
                  {tournament.matches.map((match) => {
                    const allPreviousMatchesHaveWinners = tournament.matches
                      .filter((m) => m.id < match.id)
                      .every((m) => m.winner !== null);

                    // Only players in the match see a "Play" button
                    const isPlayerInThisMatch =
                      match.players.includes(username);

                    // A match is playable if:
                    //  1) The user is in the match
                    //  2) The match doesn’t have a winner yet
                    //  3) All previous matches have a winner
                    const canPlay =
                      isPlayerInThisMatch &&
                      !match.winner &&
                      allPreviousMatchesHaveWinners;

                    const matchWinner = match.winner
                      ? tournament.display_names?.[match.winner] || match.winner
                      : "Undecided";

                    const player1 =
                      tournament.display_names?.[match.players[0]] ||
                      match.players[0];
                    const player2 =
                      tournament.display_names?.[match.players[1]] ||
                      match.players[1];

                    return (
                      <div key={match.id} className="match-container">
                        <p>
                          <strong>{player1.toUpperCase()}</strong> vs{" "}
                          <strong>{player2.toUpperCase()}</strong>
                        </p>
                        <p>Winner: {matchWinner}</p>

                        {match.in_progress && (
                          <p>
                            Currently in progress! ({match.connected_count || 0}
                            /2 players connected)
                          </p>
                        )}

                        {/* Render the Play button only if the match has no winner yet */}
                        {isPlayerInThisMatch && !match.winner && (
                          <button
                            className="btn btn-primary"
                            onClick={() => handlePlayMatch(match.id)}
                            disabled={!canPlay}
                            style={{
                              opacity: canPlay ? 1.0 : 0.5,
                              cursor: canPlay ? "pointer" : "not-allowed",
                            }}
                          >
                            Play
                          </button>
                        )}
                      </div>
                    );
                  })}
                </div>
              )}

              {/* If user is the organizer, let them close the tournament */}
              {isOrganizer && (
                <div style={{ marginTop: "20px" }}>
                  <button
                    onClick={handleCloseTournament}
                    className="btn btn-danger"
                  >
                    Close Tournament
                  </button>
                </div>
              )}
            </>
          )}
        </div>
        <div className="card-footer profile-footer d-flex justify-content-center">
          <Link to="/play/remote">Play remote</Link>
          <Link to="/play/local" className="ms-4">
            Play local
          </Link>
        </div>
      </div>
    </div>
  );
};

export default TournamentPage;
