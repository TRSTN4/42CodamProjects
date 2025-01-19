import React, { useEffect, useRef, useState } from "react";
import { useParams, useLocation } from "react-router-dom";
import "../../css/game/PongCanvas.css";
import "../../css/UserProfile.css";
import { Link } from "react-router-dom";
const wsBaseUrl = import.meta.env.VITE_WS_BASE_URL;

const WS_URL = `${wsBaseUrl}/ws/pong/`;

const RemotePongCanvas: React.FC = () => {
  const [paddleAPosition, setPaddleAPosition] = useState<number>(250);
  const [paddleBPosition, setPaddleBPosition] = useState<number>(250);
  const [ballPosition, setBallPosition] = useState<{ x: number; y: number }>({
    x: 500,
    y: 300,
  });
  const [score, setScore] = useState<{ a: number; b: number }>({ a: 0, b: 0 });
  const [gamePaused, setGamePaused] = useState<boolean>(true);
  const [gameOver, setGameOver] = useState<boolean>(false);
  const [playersConnected, setPlayersConnected] = useState<number>(0);
  const [assignedPaddle, setAssignedPaddle] = useState<"a" | "b" | null>(null);
  const [gameID, setGameID] = useState<string>("");
  const [playerKeys, setPlayerKeys] = useState<{ a?: string; b?: string }>({});
  const [winner, setWinner] = useState<string | null>(null);
  const [readyStates, setReadyStates] = useState<{ a: boolean; b: boolean }>({
    a: false,
    b: false,
  });
  const [countdown, setCountdown] = useState<boolean>(false); // New state for countdown
  const [countdownValue, setCountdownValue] = useState<number | string>(
    "ggaaaaaa!!"
  );

  const websocketRef = useRef<WebSocket | null>(null);

  const { lobbyId } = useParams<{ lobbyId: string }>();
  const location = useLocation();
  const urlParams = new URLSearchParams(location.search);
  const uniqueKey = urlParams.get("key") || "defaultKey";

  useEffect(() => {
    const connectWebSocket = () => {
      const wsUrl = lobbyId
        ? `${WS_URL}?key=${uniqueKey}&lobby=${lobbyId}`
        : `${WS_URL}?key=${uniqueKey}`;
      const websocket = new WebSocket(wsUrl);
      websocketRef.current = websocket;

      websocket.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (data.type === "assignPaddle") {
            setAssignedPaddle(data.paddle);
            if (data.game_id) setGameID(data.game_id);
            if (data.players) setPlayerKeys(data.players);
          }

          if (data.type === "playersConnected") {
            setPlayersConnected(data.count);
            setGamePaused(true);
            if (data.players) setPlayerKeys(data.players);
          }

          if (data.type === "playerReadyState") {
            setReadyStates(data.readyPlayers);
          }

          if (data.type === "update") {
            setPaddleAPosition(data.paddles.a);
            setPaddleBPosition(data.paddles.b);
            setBallPosition({ x: data.ball.x, y: data.ball.y });
            setScore(data.score);
            setGamePaused(false);
          }

          if (data.type === "gameOver") {
            setGameOver(true);
            setGamePaused(true);
            setWinner(data.winner);
          }

          // Handle countdown messages
          if (data.type === "countdownStart") {
            setCountdown(true);
            setGamePaused(true);
          }

          //   if (data.type === "redirectToTournament") {
          //     window.location.href = "/play/tournaments";
          //   }

          //   if (data.type === "redirectToPlay") {
          //     window.location.href = "/play";
          //   }

          if (data.type === "countdownEnd") {
            setCountdown(false);
            setGamePaused(false);
          }

          if (data.type === "countdown_tick") {
            setCountdownValue(data.value);
          }
        } catch (err) {
          console.error("Error parsing WebSocket message:", err);
        }
      };
    };

    connectWebSocket();
    return () => {
      if (websocketRef.current) websocketRef.current.close();
    };
  }, [uniqueKey, lobbyId]);

  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      if (
        !websocketRef.current ||
        websocketRef.current.readyState !== WebSocket.OPEN
      )
        return;
      if (event.key === "w" || event.key === "ArrowUp") {
        websocketRef.current.send(
          JSON.stringify({ type: "paddleMove", key: "up" })
        );
      } else if (event.key === "s" || event.key === "ArrowDown") {
        websocketRef.current.send(
          JSON.stringify({ type: "paddleMove", key: "down" })
        );
      }
    };

    const handleKeyUp = (event: KeyboardEvent) => {
      if (
        !websocketRef.current ||
        websocketRef.current.readyState !== WebSocket.OPEN
      )
        return;
      if (["w", "s", "ArrowUp", "ArrowDown"].includes(event.key)) {
        websocketRef.current.send(JSON.stringify({ type: "paddleStop" }));
      }
    };

    window.addEventListener("keydown", handleKeyDown);
    window.addEventListener("keyup", handleKeyUp);

    return () => {
      window.removeEventListener("keydown", handleKeyDown);
      window.removeEventListener("keyup", handleKeyUp);
    };
  }, []);

  const handleReadyUp = () => {
    if (!websocketRef.current) return;
    websocketRef.current.send(JSON.stringify({ type: "playerReady" }));
  };

  return (
    <div
      className="pong d-flex flex-column align-items-center justify-content-center vh-100"
      tabIndex={0}
      style={{ outline: "none" }}
    >
      <div className="overlap-group-wrapper">
        <div className="overlap-group">
          {gameID && <div className="lobby">{gameID}</div>}
          <div className="paddle-a" style={{ top: `${paddleAPosition}px` }} />
          <div className="paddle-b" style={{ top: `${paddleBPosition}px` }} />
          <div
            className="ball"
            style={{ left: `${ballPosition.x}px`, top: `${ballPosition.y}px` }}
          />

          <div className="overlap">
            <div className="score">
              {score.a} - {score.b}
            </div>
          </div>
        </div>

        {playerKeys.a && <div className="player-name-a">{playerKeys.a}</div>}
        {playerKeys.b && <div className="player-name-b">{playerKeys.b}</div>}

        {gameOver && (
          <div className="game-over">
            <h2 className="winner-text">
              {winner ? `${winner.toUpperCase()} WINS!` : "No one wins!"}
            </h2>
            <Link to="/play" className="btn btn-primary mt-4">
              {" "}
              Back to lobby
            </Link>
          </div>
        )}

        {gamePaused &&
          !gameOver &&
          !countdown && ( // Hide this section during countdown
            <div className="game-paused">
              {playersConnected < 2 ? (
                <h3 className="text">Waiting for another player...</h3>
              ) : (
                <h3 className="text-white">
                  {" "}
                  Waiting for players to ready up...
                </h3>
              )}
              <p className="fst-italic">
                Players connected: {playersConnected}/2
              </p>
              {assignedPaddle && (
                <>
                  <p>
                    {playerKeys.a ? playerKeys.a : "Unknown"} ready:{" "}
                    <strong>{readyStates.a ? "Yes" : "No"}</strong>
                    <br />
                    {playerKeys.b ? playerKeys.b : "Unknown"} ready:{" "}
                    <strong>{readyStates.b ? "Yes" : "No"}</strong>
                  </p>
                  {!readyStates[assignedPaddle] && (
                    <button
                      className="glass-button-ready"
                      onClick={handleReadyUp}
                    >
                      Ready Up
                    </button>
                  )}
                </>
              )}
            </div>
          )}

        {countdown && ( // Show countdown message
          <div className="countdown">{countdownValue}</div>
        )}

        {assignedPaddle && (
          <div className="player-info">
            <h5 className="instruction">
              YOU ARE CONTROLLING THE{" "}
              {assignedPaddle === "a" ? "LEFT" : "RIGHT"} PADDLE | USE "W"/"S"
              OR "<span className="arrow-char">↑</span>"/"
              <span className="arrow-char">↓</span>"
            </h5>
          </div>
        )}
      </div>
    </div>
  );
};

export default RemotePongCanvas;
