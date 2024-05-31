#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <string>

class Zombie {
private:
    std::string name;

public:
    Zombie() : name("DefaultZombie") {}
    Zombie(std::string name);
    ~Zombie();
    void announce() const;
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);
Zombie* zombieHorde(int N, std::string name);

#endif
