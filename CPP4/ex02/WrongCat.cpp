#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat") {
    std::cout << "WrongCat constructor called\n";
}

WrongCat::~WrongCat() {
    std::cout << "WrongCat destructor called\n";
}

WrongCat::WrongCat(const WrongCat& src): WrongAnimal(src) {
    std::cout << "WrongCat copy constructor called\n";
    *this = src;
}

WrongCat& WrongCat::operator=(const WrongCat& src) {
    std::cout << "WrongCat copy assignment operator called\n";
    if (this != &src)
        type = src.type;
    return *this;
}

void WrongCat::makeSound() const {
    std::cout << "Meow!\n";
}
