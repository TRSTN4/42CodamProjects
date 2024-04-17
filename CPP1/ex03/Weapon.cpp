#include "Weapon.h"

Weapon::Weapon(const std::string weaponType) {
    type = weaponType;
}

const std::string& Weapon::getType() const {
    return (type);
}

void Weapon::setType(const std::string newType) {
    type = newType;
}
