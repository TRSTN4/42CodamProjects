#include "./Zombie.h"

void randomChump(std::string name) {
    Zombie stackZombie(name);
    stackZombie.announce();
}
