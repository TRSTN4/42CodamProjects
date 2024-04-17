#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    ScavTrap empty;
    ScavTrap soldier("Soldier");
    ScavTrap spy(soldier);

    empty.attack("Skeleton");
    spy.attack("Zombie");
    
    soldier.beRepaired(15);
    soldier.takeDamage(5);
    soldier.beRepaired(15);
    soldier.takeDamage(5);
    soldier.takeDamage(5);
    soldier.beRepaired(15);
    soldier.takeDamage(5);
    soldier.attack("Zombie");

    spy.guardGate();

    return 0;
}
