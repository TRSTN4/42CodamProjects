#include "Cat.hpp"
    
Cat::Cat(): Animal("Cat") {
    std::cout << "Cat constructor called\n";
    brain = new (std::nothrow) Brain();
    if (!brain)
        std::cout << "Memory Allocation failed\n";
}

Cat::~Cat() {
    std::cout << "Cat destructor called\n";
    delete brain;
}

Cat::Cat(const Cat& src): Animal(src) {
    std::cout << "Cat copy constructor called\n";
    brain = new (std::nothrow) Brain(*src.brain);
    if (!brain) {
        std::cout << "Memory allocation failed\n";
        exit(1);
    }
}

Cat& Cat::operator=(const Cat& src) {
    if (this != &src) {
        type = src.type;

        Brain* newBrain = new (std::nothrow) Brain(*src.brain);
        if (!newBrain) {
            std::cout << "Memory allocation failed\n";
            exit(1);
        } else {
            delete brain;
            brain = newBrain;
        }
        std::cout << "Cat copy assignment operator called\n";
    }
    return *this;
}

void Cat::makeSound() const {
    std::cout << "Meow!\n";
}

void Cat::setIdea(int index, const std::string& idea) const {
    brain->setIdea(index, idea);
}

std::string Cat::getIdea(int index) const {
    return brain->getIdea(index);
}
