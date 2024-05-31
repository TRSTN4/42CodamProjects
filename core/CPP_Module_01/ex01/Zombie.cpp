#include "./Zombie.h"

Zombie::Zombie(std::string zombieName) {
    name = zombieName;
}

Zombie::~Zombie() {
    std::cout << name << " is killed by destructor.\n";
}

void Zombie::announce() const {
    std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}
