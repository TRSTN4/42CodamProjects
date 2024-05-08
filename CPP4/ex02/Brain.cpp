#include "Brain.hpp"

Brain::Brain() {
    std::cout << "Brain constructor called\n";
}

Brain::~Brain() {
    std::cout << "Brain destructor called\n";
}

Brain::Brain(const Brain& src) {
    std::cout << "Brain copy constructor called\n";
    *this = src;
}

Brain& Brain::operator=(const Brain& src) {
    std::cout << "Brain assignment operator called\n";
    if (this != &src) {
        for (int i = 0; i < 100; i++) {
            ideas[i] = src.ideas[i];
        }
    }
    return *this;
}
