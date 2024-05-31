#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    FragTrap empty;
    FragTrap soldier("Soldier");
    FragTrap spy(soldier);

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

    spy.highFivesGuys();

    return 0;
}
