import Register from "./pages/RegisterPage";
import "./App.css";
import LoginPage from "./pages/LoginPage";
import LandingPage from "./pages/LandingPage";
import Home from "./pages/HomePage";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import NotFoundPage from "./error_pages/404NotFound";
import ProtectedRoute from "./components/utils/ProtectedRoute";
import ChatPage from "./pages/ChatPage";
import UserProfileWrapper from "./components/users/UserProfileWrapper";
import CallBack from "./pages/CallBack";
import UsersPage from "./pages/UsersPage";
import FriendsPage from "./pages/FriendsPage";
import SpinningLogo from "./components/SpinningLogo";
import GameMainPage from "./pages/GameMainPage";
import RemoteLobbyList from "./components/game/RemoteLobbyList";
import RemotePongCanvas from "./components/game/RemotePongCanvas";
import LocalPongCanvas from "./components/game/LocalPongCanvas";
import TournamentPage from "./components/game/TournamentPage";
import ChangeDetailsWrapper from "./components/users/ChangeDetailsWrapper";
import { useAuth } from "./components/utils/AuthContext";

const App = () => {
  return (
    <div className="App">
      <Router>
        <AppRoutes />
      </Router>
    </div>
  );
};

const AppRoutes = () => {
  const { userId, isAuthChecked } = useAuth();

  if (!isAuthChecked) {
    // Show loading spinner until auth check is complete
    return <SpinningLogo />;
  }

  return (
    <Routes>
      <Route path="/hello" element={<LandingPage />} />
      <Route
        path="/login"
        element={<LoginPage userId={userId} isAuthChecked={isAuthChecked} />}
      />
      <Route
        path="/register"
        element={<Register userId={userId} isAuthChecked={isAuthChecked} />}
      />
      <Route path="/42-callback" element={<CallBack />} />
      <Route path="*" element={<NotFoundPage />} />
      <Route
        path="/"
        element={<Home userId={userId} isAuthChecked={isAuthChecked} />}
      />
      <Route element={<ProtectedRoute userId={userId} />}>
        <Route path="/users" element={<UsersPage />} />
        <Route path="/users/edit" element={<ChangeDetailsWrapper />} />
        <Route path="/users/:username" element={<UserProfileWrapper />} />
        <Route path="/chat" element={<ChatPage userId={userId} />} />
        <Route path="/friends" element={<FriendsPage />} />
        <Route path="/play" element={<GameMainPage />} />
        <Route path="/play/remote" element={<RemoteLobbyList />} />
        <Route path="/play/remote/:lobbyId" element={<RemotePongCanvas />} />
        <Route path="/play/local" element={<LocalPongCanvas />} />
        <Route path="/play/tournaments" element={<TournamentPage />} />
      </Route>
    </Routes>
  );
};

export default App;
