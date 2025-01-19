import React from "react";
import { Navbar, Nav } from "react-bootstrap";
import "../css/NavBar.css";

const NavBar: React.FC<{ username: string }> = ({ username }) => {
  return (
    <div className="">
      <Navbar bg="transparent" variant="dark" className="w-100 fs-4 fixed-top">
        <Nav className="mx-auto text-center glass-navx mt-3">
          <Nav.Link href="/" className="glass-navx-item">
            Home
          </Nav.Link>
          <Nav.Link href="/play" className="glass-navx-item">
            Play
          </Nav.Link>
          <Nav.Link href="/chat" className="glass-navx-item">
            Messages
          </Nav.Link>
          <Nav.Link href="/friends" className="glass-navx-item">
            Friends
          </Nav.Link>
          <Nav.Link href="/users" className="glass-navx-item">
            Browse users
          </Nav.Link>
          <Nav.Link href={`/users/${username}`} className="glass-navx-item">
            Profile
          </Nav.Link>
        </Nav>
      </Navbar>
    </div>
  );
};

export default NavBar;
