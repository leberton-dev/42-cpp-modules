#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed (void) : _value (0) {
}

Fixed::Fixed (const Fixed& src) {
    *this = src;
}

Fixed::Fixed (const int value) {
    this->_value = value << this->_fractionalBits;
}

Fixed::Fixed (const float value) {

    this->_value = roundf (value * (1 << this->_fractionalBits));
}

Fixed::~Fixed (void) {
}

Fixed& Fixed::operator= (const Fixed& rhs) {
    if (this != &rhs)
        this->_value = rhs._value;
    return *this;
}

bool Fixed::operator== (const Fixed& rhs) const {
    return this->_value == rhs._value;
}

bool Fixed::operator!= (const Fixed& rhs) const {
    return this->_value != rhs._value;
}

bool Fixed::operator< (const Fixed& rhs) const {
    return this->_value < rhs._value;
}

bool Fixed::operator> (const Fixed& rhs) const {
    return this->_value > rhs._value;
}

bool Fixed::operator<= (const Fixed& rhs) const {
    return this->_value <= rhs._value;
}

bool Fixed::operator>= (const Fixed& rhs) const {
    return this->_value >= rhs._value;
}

Fixed Fixed::operator+ (const Fixed& rhs) const {
    Fixed result;
    result.setRawBits (this->_value + rhs._value);
    return result;
}

Fixed Fixed::operator- (const Fixed& rhs) const {
    Fixed result;
    result.setRawBits (this->_value - rhs._value);
    return result;
}

Fixed Fixed::operator* (const Fixed& rhs) const {
    Fixed result;
    long temp = (long)this->_value * rhs._value;
    result.setRawBits ((int)(temp >> this->_fractionalBits));
    return result;
}

Fixed Fixed::operator/ (const Fixed& rhs) const {
    if (rhs._value == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        return Fixed ();
    }
    Fixed result;
    long temp = ((long)this->_value << this->_fractionalBits) / rhs._value;
    result.setRawBits ((int)temp);
    return result;
}

Fixed& Fixed::operator++ () {
    this->_value++;
    return *this;
}

Fixed Fixed::operator++ (int) {
    Fixed temp (*this);
    this->_value++;
    return temp;
}

Fixed& Fixed::operator-- () {
    this->_value--;
    return *this;
}

Fixed Fixed::operator-- (int) {
    Fixed temp (*this);
    this->_value--;
    return temp;
}

int Fixed::getRawBits (void) const {
    return this->_value;
}

void Fixed::setRawBits (int const raw) {
    this->_value = raw;
}

float Fixed::toFloat (void) const {
    return (float)this->_value / (1 << this->_fractionalBits);
}

int Fixed::toInt (void) const {
    return this->_value >> this->_fractionalBits;
}

Fixed& Fixed::min (Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max (Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

Fixed const& Fixed::min (const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

Fixed const& Fixed::max (const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}

std::ostream& operator<< (std::ostream& o, Fixed const& i) {
    o << i.toFloat ();
    return o;
}
