#include "Cat.hpp"
    
Cat::Cat(): AAnimal("Cat") {
    std::cout << "Cat constructor called\n";
    brain = new (std::nothrow) Brain();
    if (!brain)
        std::cout << "Memory Allocation failed\n";
}

Cat::~Cat() {
    std::cout << "Cat destructor called\n";
    delete brain;
}

Cat::Cat(const Cat& src): AAnimal(src) {
    std::cout << "Cat copy constructor called\n";
    brain = new (std::nothrow) Brain(*src.brain);
    if (!brain) {
        std::cout << "Memory allocation failed\n";
    }
}

Cat& Cat::operator=(const Cat& src) {
    if (this != &src) {
        type = src.type;

        Brain* newBrain = new (std::nothrow) Brain(*src.brain);
        if (!newBrain) {
            std::cout << "Memory allocation failed\n";
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
