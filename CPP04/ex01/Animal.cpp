#include "Animal.hpp"

Animal::Animal(): type("Default") {
    std::cout << "Animal Default constructor called\n";
}

Animal::Animal(std::string type): type(type) {
    std::cout << "Animal " << type << " constructor called\n";
}

Animal::~Animal() {
    std::cout << "Animal " << type << " destructor called\n";
}

Animal::Animal(const Animal& src) {
    std::cout << "Animal " << src.type << " copy constructor called\n";
    *this = src;
}

Animal& Animal::operator=(const Animal& src) {
    std::cout << "Animal " << src.type << " assignment operator called\n";
    if (this != &src)
        type = src.type;
    return *this;
}

void Animal::makeSound() const {
    std::cout << "Animal makeSound called\n";
}

std::string Animal::getType() const {
    return type;
}
