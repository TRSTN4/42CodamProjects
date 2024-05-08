#include "Dog.hpp"

Dog::Dog(): Animal("Dog") {
    std::cout << "Dog constructor called\n";
}

Dog::~Dog() {
    std::cout << "Dog destructor called\n";
}

Dog::Dog(const Dog& src): Animal(src) {
    std::cout << "Dog copy constructor called\n";
    *this = src;
}

Dog& Dog::operator=(const Dog& src) {
    std::cout << "Dog copy assignment operator called\n";
    if (this != &src)
        type = src.type;
    return *this;
}

void Dog::makeSound() const {
    std::cout << "Woof!\n";
}
