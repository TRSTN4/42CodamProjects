#include "Fixed.hpp"

Fixed::Fixed(): value(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(const int intValue): value(intValue << fractionalBits) {
    std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float floatValue): value(roundf(floatValue * (1 << fractionalBits))) {
    std::cout << "Float constructor called\n";
}

Fixed::Fixed(const Fixed &other) : value(0) {
    std::cout << "Copy constructor called\n";
    *this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        value = other.value;
        std::cout << "Copy assignment operator called\n";
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called\n";
}

float Fixed::toFloat(void) const {
    return static_cast<float>(value) / (1 << fractionalBits);
}

int Fixed::toInt(void) const {
    return value >> fractionalBits;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}
