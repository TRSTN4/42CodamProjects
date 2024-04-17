#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap default constructor called\n";
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap parameterized constructor called\n";
}

FragTrap::FragTrap(FragTrap const &other) : ClapTrap(other) {
    std::cout << "FragTrap copy constructor called\n";
    *this = other;
}

FragTrap &FragTrap::operator=(FragTrap const &other) {
    if (this != &other) {
        name = other.name;
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
    }
    std::cout << "FragTrap copy assignment operator called\n";
    return *this;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap destructor called\n";
}

void FragTrap::attack(const std::string &target) {
    if (energyPoints > 0 && hitPoints > 0) {
        std::cout << "FragTrap " << name << " blasts " << target << ", dealing " << attackDamage << " points of damage!\n";
        energyPoints--;
    }
    else
        std::cout << "FragTrap " << name << " can't attack because no hit points and/or energy points left.\n";
}

void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << name << " gives a high five!\n";
}
