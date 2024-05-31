#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Default"), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap default constructor called\n";
}

ClapTrap::ClapTrap(const std::string &name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap parameterized constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap &other) 
    : name(other.name), hitPoints(other.hitPoints), energyPoints(other.energyPoints), attackDamage(other.attackDamage) {
    std::cout << "ClapTrap copy constructor called\n";
    *this = other;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    if (this != &other) {
        name = other.name;
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
    }
    std::cout << "ClapTrap copy assignment operator called\n";
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap destructor called\n";
}

void ClapTrap::attack(const std::string &target) {
    if (energyPoints > 0 && hitPoints > 0) {
        std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!\n";
        energyPoints--;
    }
    else
        std::cout << "ClapTrap " << name << " can't attack because no hit points and/or energy points left.\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (hitPoints > 0) {
        std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!\n";
        hitPoints -= amount;
    }
    else
        std::cout << "ClapTrap " << name << " is out of hit points.\n";
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (energyPoints > 0 && hitPoints > 0) {
        if (hitPoints + amount > 10)
        {
            std::cout << "ClapTrap " << name << " is repairing over its maximum capacity, recovering max 10 hit points.\n";
            hitPoints = 10;
            energyPoints--;
        }
        else {
            std::cout << "ClapTrap " << name << " is repairing, recovering " << amount << " hit points.\n";
            hitPoints += amount;
            energyPoints--;
        }
    }
    else
        std::cout << "ClapTrap " << name << " can't repair because no hit points and/or energy points left.\n";
}
