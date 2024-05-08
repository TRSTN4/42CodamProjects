#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): type("Default") {
    std::cout << "WrongAnimal Default constructor called\n";
}

WrongAnimal::WrongAnimal(std::string type): type(type) {
    std::cout << "WrongAnimal " << type << " constructor called\n";
}

WrongAnimal::~WrongAnimal() {
    std::cout << "WrongAnimal " << type << " destructor called\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& src) {
    std::cout << "WrongAnimal copy constructor called\n";
    *this = src;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& src) {
    std::cout << "WrongAnimal assignment operator called\n";
    if (this != &src)
        type = src.type;
    return *this;
}

void WrongAnimal::makeSound() const {
    std::cout << "WrongAnimal makeSound called\n";
}

std::string WrongAnimal::getType() const {
    return type;
}
