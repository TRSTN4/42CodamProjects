#include "./Zombie.h"

Zombie* zombieHorde(int N, std::string name) {
    Zombie* horde = new Zombie[N];

    for (int i = 0; i < N; i++) {
        new (horde + i) Zombie(name + std::to_string(i + 1));
    }

    return (horde);
}
