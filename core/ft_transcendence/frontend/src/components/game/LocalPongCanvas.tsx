import React, { useRef, useEffect, useState } from "react";

type PaddleKey = "a" | "b";
interface GameState {
  paddles: Record<PaddleKey, number>;
  ball: { x: number; y: number; dx: number; dy: number };
  score: Record<PaddleKey, number>;
  paddleDirections: Record<PaddleKey, number>;
  gameStarted: boolean;
}

const MAX_SCORE = 3;
const PADDLE_SPEED = 5;
const CANVAS_WIDTH = 1000;
const CANVAS_HEIGHT = 600;
const PADDLE_HEIGHT = 100;
const BALL_SIZE = 10;

const LocalPongCanvas: React.FC = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const containerRef = useRef<HTMLDivElement>(null);

  const [countdown, setCountdown] = useState(0);
  const [countingDown, setCountingDown] = useState(false);

  // New states for winner screen
  const [winner, setWinner] = useState<"A" | "B" | null>(null);
  const [showWinnerScreen, setShowWinnerScreen] = useState(false);

  const [game, setGame] = useState<GameState>({
    paddles: { a: 250, b: 250 },
    ball: { x: 500, y: 300, dx: 1, dy: 1 },
    score: { a: 0, b: 0 },
    paddleDirections: { a: 0, b: 0 },
    gameStarted: false,
  });

  const gameOver = game.score.a >= MAX_SCORE || game.score.b >= MAX_SCORE;

  useEffect(() => {
    if (countingDown && countdown > 0) {
      const timer = setTimeout(() => setCountdown((c) => c - 1), 1000);
      return () => clearTimeout(timer);
    }
    if (countingDown && countdown === 0) {
      setGame((prev) => ({ ...prev, gameStarted: true }));
      setCountingDown(false);
    }
  }, [countdown, countingDown]);

  useEffect(() => {
    const ctx = canvasRef.current?.getContext("2d");
    let animationFrameId: number;

    const draw = () => {
      if (!ctx) return;
      ctx.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

      // paddles
      ctx.fillStyle = "white";
      ctx.fillRect(0, game.paddles.a, 10, PADDLE_HEIGHT);
      ctx.fillRect(CANVAS_WIDTH - 10, game.paddles.b, 10, PADDLE_HEIGHT);

      // ball
      ctx.beginPath();
      ctx.arc(game.ball.x, game.ball.y, BALL_SIZE, 0, 2 * Math.PI);
      ctx.fill();

      // score
      ctx.font = "20px Arial";
      ctx.fillText(`Score: ${game.score.a}`, 50, 50);
      ctx.fillText(`Score: ${game.score.b}`, CANVAS_WIDTH - 150, 50);

      animationFrameId = requestAnimationFrame(draw);
    };

    draw();
    return () => cancelAnimationFrame(animationFrameId);
  }, [game]);

  useEffect(() => {
    let intervalId: NodeJS.Timeout;
    if (game.gameStarted && !showWinnerScreen) {
      intervalId = setInterval(() => {
        setGame((prev) => updateGameState(prev));
      }, 1000 / 60);
    }
    return () => clearInterval(intervalId);
  }, [game.gameStarted, showWinnerScreen]);

  // If showWinnerScreen is true, wait 3s then reset
  useEffect(() => {
    if (showWinnerScreen) {
      const timer = setTimeout(() => {
        handleFullReset();
      }, 6000);
      return () => clearTimeout(timer);
    }
  }, [showWinnerScreen]);

  // Focus so we can listen to keyboard
  useEffect(() => {
    containerRef.current?.focus();
  }, []);

  const startGame = () => {
    // If there's a winner screen, ignore until it resets
    if (winner) return;
    if (gameOver) return;

    setCountdown(3);
    setCountingDown(true);
    containerRef.current?.focus();
  };

  const resetBall = (st: GameState): GameState => {
    return {
      ...st,
      ball: {
        x: CANVAS_WIDTH / 2,
        y: CANVAS_HEIGHT / 2,
        dx: st.ball.dx > 0 ? -1 : 1,
        dy: 1,
      },
    };
  };

  const resetGame = (): GameState => {
    return {
      paddles: { a: 250, b: 250 },
      ball: { x: 500, y: 300, dx: 1, dy: 1 },
      score: { a: 0, b: 0 },
      paddleDirections: { a: 0, b: 0 },
      gameStarted: false,
    };
  };

  // Called after the 3-second winner screen
  const handleFullReset = () => {
    setWinner(null);
    setShowWinnerScreen(false);
    setGame(resetGame());
  };

  // pause game, start new countdown
  const pauseAndCountdown = (st: GameState) => {
    setCountingDown(true);
    setCountdown(3);
    return { ...st, gameStarted: false };
  };

  const updateGameState = (st: GameState): GameState => {
    // If the game hasn't started, do nothing
    if (!st.gameStarted) return st;

    let { paddles, ball, score, paddleDirections } = JSON.parse(
      JSON.stringify(st)
    );

    // Move paddles
    paddles.a += paddleDirections.a * PADDLE_SPEED;
    paddles.b += paddleDirections.b * PADDLE_SPEED;
    paddles.a = Math.max(0, Math.min(500, paddles.a));
    paddles.b = Math.max(0, Math.min(500, paddles.b));

    // Move ball
    ball.x += ball.dx * 5;
    ball.y += ball.dy * 5;

    // Bounce off top/bottom
    if (ball.y <= 0 || ball.y >= CANVAS_HEIGHT - BALL_SIZE - 20) {
      ball.dy *= -1;
    }

    // Paddle collision
    if (
      ball.x <= 10 &&
      ball.y >= paddles.a &&
      ball.y <= paddles.a + PADDLE_HEIGHT
    ) {
      ball.dx *= -1.05;
      ball.dy *= 1.05;
    } else if (
      ball.x >= CANVAS_WIDTH - 40 &&
      ball.y >= paddles.b &&
      ball.y <= paddles.b + PADDLE_HEIGHT
    ) {
      ball.dx *= -1.05;
      ball.dy *= 1.05;
    }

    // Scoring logic
    if (ball.x < 0) {
      score.b += 1;

      // Create an updatedState so the scoreboard can re-render to show 3
      const updatedState = { ...st, paddles, ball, score, paddleDirections };

      // If winner, show scoreboard update THEN winner screen
      if (score.b >= MAX_SCORE) {
        // Return the updated scoreboard first
        setTimeout(() => {
          setWinner("B");
          setShowWinnerScreen(true);
        }, 0);
        return { ...updatedState, gameStarted: false };
      } else {
        updatedState.ball = resetBall(updatedState).ball;
        return pauseAndCountdown(updatedState);
      }
    }

    if (ball.x > CANVAS_WIDTH) {
      score.a += 1;

      const updatedState = { ...st, paddles, ball, score, paddleDirections };

      if (score.a >= MAX_SCORE) {
        setTimeout(() => {
          setWinner("A");
          setShowWinnerScreen(true);
        }, 0);
        return { ...updatedState, gameStarted: false };
      } else {
        updatedState.ball = resetBall(updatedState).ball;
        return pauseAndCountdown(updatedState);
      }
    }

    // Return updated state
    return { ...st, paddles, ball, score };
  };

  const handleKeyDown = (e: React.KeyboardEvent) => {
    if (!game.gameStarted) return;
    setGame((prev) => {
      const pd = { ...prev.paddleDirections };
      if (e.key === "w") pd.a = -1;
      if (e.key === "s") pd.a = 1;
      if (e.key === "ArrowUp") pd.b = -1;
      if (e.key === "ArrowDown") pd.b = 1;
      return { ...prev, paddleDirections: pd };
    });
  };

  const handleKeyUp = (e: React.KeyboardEvent) => {
    setGame((prev) => {
      const pd = { ...prev.paddleDirections };
      if (e.key === "w" || e.key === "s") pd.a = 0;
      if (e.key === "ArrowUp" || e.key === "ArrowDown") pd.b = 0;
      return { ...prev, paddleDirections: pd };
    });
  };

  return (
    <div
      className="pong d-flex flex-column align-items-center justify-content-center vh-100"
      ref={containerRef}
      tabIndex={0}
      onKeyDown={handleKeyDown}
      onKeyUp={handleKeyUp}
      style={{ outline: "none" }}
    >
      <div className="overlap-group-wrapper">
        <div className="overlap-group">
          <div className="paddle-a" style={{ top: `${game.paddles.a}px` }} />
          <div className="paddle-b" style={{ top: `${game.paddles.b}px` }} />
          <div
            className="ball"
            style={{ left: `${game.ball.x}px`, top: `${game.ball.y}px` }}
          />
          <div className="overlap">
            <div className="score">
              {game.score.a} - {game.score.b}
            </div>
          </div>
        </div>

        <div className="player-name-a">Player A</div>
        <div className="player-name-b">Player B</div>

        {/* Winner screen */}
        {showWinnerScreen && winner && (
          <div className="game-over">
            <h2 className="winner-text">Player {winner} Won!</h2>
          </div>
        )}

        {/* Countdown */}
        {countingDown && countdown > 0 && (
          <div className="countdown">{countdown}</div>
        )}
        <div className="player-info d-flex justify-space-between">
          <h5 className="instruction">
            PLAYER A USES THE LEFT PADDLE AND USES THE "W"/"S KEYS{" "}
          </h5>
          <h5 className="instruction">
            PLAYER B USES THE RIGHT PADDLE AND USES THE ARROW KEYS{" "}
          </h5>
        </div>

        {/* Start button */}
        {!game.gameStarted && !countingDown && !showWinnerScreen && (
          <div className="game-paused">
            <h3 className="mb-5">
              <strong>Press START GAME to play</strong>
            </h3>
            <button className="glass-button-ready" onClick={startGame}>
              Start Game
            </button>
          </div>
        )}
      </div>
    </div>
  );
};

export default LocalPongCanvas;
