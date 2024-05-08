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

void Brain::setIdea(int index, const std::string& idea) {
    if (index >= 0 && index < 100) {
        ideas[index] = idea;
    } else {
        std::cout << "Invalid idea index: " << index << "\n";
    }
}

std::string Brain::getIdea(int index) const {
    if (index >= 0 && index < 100) {
        return ideas[index];
    }
    return "Invalid idea index";
}
