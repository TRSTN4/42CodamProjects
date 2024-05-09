#include "AAnimal.hpp"

AAnimal::AAnimal(): type("Default") {
    std::cout << "AAnimal Default constructor called\n";
}

AAnimal::AAnimal(std::string type): type(type) {
    std::cout << "AAnimal " << type << " constructor called\n";
}

AAnimal::~AAnimal() {
    std::cout << "AAnimal " << type << " destructor called\n";
}

AAnimal::AAnimal(const AAnimal& src) {
    std::cout << "AAnimal " << src.type << " copy constructor called\n";
    *this = src;
}

AAnimal& AAnimal::operator=(const AAnimal& src) {
    std::cout << "AAnimal " << src.type << " assignment operator called\n";
    if (this != &src)
        type = src.type;
    return *this;
}

void AAnimal::makeSound() const {
    std::cout << "AAnimal makeSound called\n";
}

std::string AAnimal::getType() const {
    return type;
}
