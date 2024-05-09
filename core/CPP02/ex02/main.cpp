#include "Fixed.hpp"

#include <iostream>

int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	
	std::cout << a << "\n";
	std::cout << ++a << "\n";
	std::cout << a << "\n";
	std::cout << a++ << "\n";
	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << Fixed::max( a, b ) << "\n";
	
	return 0;
}
