#include "Fixed.hpp"

Fixed::Fixed (void) : _value (0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed (const Fixed& src) {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed::Fixed (const int value) {
    std::cout << "Int constructor called" << std::endl;
    this->_value = value << this->_fractionalBits;
}

Fixed::Fixed (const float value) {
    std::cout << "Float constructor called" << std::endl;
    float scaledValue = value * (1 << this->_fractionalBits);
    this->_value      = (int)(scaledValue + (scaledValue >= 0 ? 0.5f : -0.5f));
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

float Fixed::toFloat (void) const {
    return (float)this->_value / (1 << this->_fractionalBits);
}

int Fixed::toInt (void) const {
    return this->_value >> this->_fractionalBits;
}

std::ostream& operator<< (std::ostream& o, Fixed const& i) {
    o << i.toFloat ();
    return o;
}
