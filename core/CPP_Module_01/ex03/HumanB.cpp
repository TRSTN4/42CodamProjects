#include "HumanB.h"

#include <iostream>

HumanB::HumanB(const std::string& humanName) : name(humanName), weapon(NULL) {}

void HumanB::setWeapon(Weapon& weaponType) {
    weapon = &weaponType;
}

void HumanB::attack() const {
    if (weapon)
        std::cout << name << " attacks with their " << weapon->getType() << "\n";
    else
        std::cout << name << " is unarmed\n";
}
