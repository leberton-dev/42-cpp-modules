#include "Fixed.hpp"

#include <iostream>

Fixed::Fixed (void) : _value (0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed (const Fixed& src) {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed::~Fixed (void) {
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator= (const Fixed& rhs) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_value = rhs._value;
    return *this;
}

int Fixed::getRawBits (void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_value;
}

void Fixed::setRawBits (int const raw) {
    std::cout << "setRawBits member function called" << std::endl;
    this->_value = raw;
}
