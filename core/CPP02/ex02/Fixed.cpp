#include "Fixed.hpp"

Fixed::~Fixed() {}

Fixed::Fixed(): value(0) {}

Fixed::Fixed(const int intValue): value(intValue << fractionalBits) {}

Fixed::Fixed(const float floatValue): value(static_cast<int>(roundf(floatValue * (1 << fractionalBits)))) {}

Fixed::Fixed(const Fixed &other): value(other.value) {}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other)
        this->value = other.value;
    return *this;
}

int Fixed::getRawBits(void) const {
    return value;
}

void Fixed::setRawBits(int const raw) {
    value = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(value) / (1 << fractionalBits);
}

int Fixed::toInt(void) const {
    return value >> fractionalBits;
}

bool Fixed::operator>(const Fixed &other) const {
    return value > other.value;
}

bool Fixed::operator<(const Fixed &other) const {
    return value < other.value;
}

bool Fixed::operator>=(const Fixed &other) const {
    return value >= other.value;
}

bool Fixed::operator<=(const Fixed &other) const {
    return value <= other.value;
}

bool Fixed::operator==(const Fixed &other) const {
    return value == other.value;
}

bool Fixed::operator!=(const Fixed &other) const {
    return value != other.value;
}

Fixed Fixed::operator+(const Fixed &other) const {
    return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const {
    return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const {
    return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const {
    if (other.value == 0) {
        std::cerr << "Division by zero\n";
        exit(EXIT_FAILURE);
    }
    return Fixed(this->toFloat() / other.toFloat());
}

Fixed &Fixed::operator++() {
    value++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    value++;
    return temp;
}

Fixed &Fixed::operator--() {
    value--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    value--;
    return temp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    if (a < b)
        return a;
    else
        return b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    if (a < b)
        return a;
    else
        return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    if (a > b)
        return a;
    else
        return b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    if (a > b)
        return a;
    else
        return b;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}
