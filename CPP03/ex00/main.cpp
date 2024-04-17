#include "ClapTrap.hpp"

int main() {
    ClapTrap clapTrap;
    ClapTrap soldier("Soldier");
    ClapTrap spy(soldier);

    clapTrap.attack("Zombie");
    
    soldier.beRepaired(15);
    soldier.takeDamage(5);
    soldier.beRepaired(15);
    soldier.takeDamage(5);
    soldier.takeDamage(5);
    soldier.beRepaired(15);
    soldier.takeDamage(5);
    soldier.attack("Zombie");

    return 0;
}
