#include "HumanA.h"

#include <iostream>

HumanA::HumanA(const std::string& humanName, Weapon& weaponType) : name(humanName), weapon(weaponType) {}

void HumanA::attack() const {
    std::cout << name << " attacks with their " << weapon.getType() << "\n";
}
