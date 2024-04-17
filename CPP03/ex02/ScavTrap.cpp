#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("Default") {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "FragTrap default constructor called\n";
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap parameterized constructor called\n";
}

ScavTrap::ScavTrap(ScavTrap const &other) : ClapTrap(other) {
    std::cout << "ScavTrap copy constructor called\n";
    *this = other;
}

ScavTrap &ScavTrap::operator=(ScavTrap const &other) {
    if (this != &other) {
        name = other.name;
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
    }
    std::cout << "ScavTrap copy assignment operator called\n";
    return *this;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap destructor called\n";
}

void ScavTrap::attack(const std::string &target) {
    if (energyPoints > 0 && hitPoints > 0) {
        std::cout << "ScavTrap " << name << " hits " << target << ", dealing " << attackDamage << " points of damage!\n";
        energyPoints--;
    }
    else
        std::cout << "ScavTrap " << name << " can't attack because no hit points and/or energy points left.\n";
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name << " is now in Gate Keeper mode.\n";
}
