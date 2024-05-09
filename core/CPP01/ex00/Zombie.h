#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <string>

class Zombie {
    private:
        std::string name;

    public:
        Zombie(std::string name);
        ~Zombie();
        void announce() const;
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);

#endif
