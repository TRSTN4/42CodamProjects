#include "Cat.hpp"

Cat::Cat(): Animal("Cat") {
    std::cout << "Cat constructor called\n";
}

Cat::~Cat() {
    std::cout << "Cat destructor called\n";
}

Cat::Cat(const Cat& src): Animal(src) {
    std::cout << "Cat copy constructor called\n";
    *this = src;
}

Cat& Cat::operator=(const Cat& src) {
    std::cout << "Cat copy assignment operator called\n";
    if (this != &src)
        type = src.type;
    return *this;
}

void Cat::makeSound() const {
    std::cout << "Meow!\n";
}
