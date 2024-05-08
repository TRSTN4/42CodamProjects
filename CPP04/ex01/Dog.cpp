#include "Dog.hpp"

Dog::Dog(): Animal("Dog") {
    std::cout << "Dog constructor called\n";
    brain = new (std::nothrow) Brain();
    if (!brain)
        std::cout << "Memory Allocation failed\n";
}

Dog::~Dog() {
    std::cout << "Dog destructor called\n";
    delete brain;
}

Dog::Dog(const Dog& src): Animal(src) {
    std::cout << "Dog copy constructor called\n";
    brain = new (std::nothrow) Brain(*src.brain);
    if (!brain) {
        std::cout << "Memory allocation failed\n";
        exit(1);
    }
}

Dog& Dog::operator=(const Dog& src) {
    if (this != &src) {
        type = src.type;

        Brain* newBrain = new (std::nothrow) Brain(*src.brain);
        if (!newBrain) {
            std::cout << "Memory allocation for Brain failed during assignment\n";
            exit(1);
        } else {
            delete brain;
            brain = newBrain;
        }
        std::cout << "Dog copy assignment operator called\n";
    }
    return *this;
}

void Dog::makeSound() const {
    std::cout << "Woof!\n";
}

void Dog::setIdea(int index, const std::string& idea) const {
    brain->setIdea(index, idea);
}

std::string Dog::getIdea(int index) const {
    return brain->getIdea(index);
}
