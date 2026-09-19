#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
    public:
    Fixed (void);
    Fixed (const Fixed& src);
    Fixed (const int value);
    Fixed (const float value);
    ~Fixed (void);

    Fixed& operator= (const Fixed& rhs);

    int getRawBits (void) const;
    void setRawBits (int const raw);
    float toFloat (void) const;
    int toInt (void) const;

    private:
    int _value;
    static const int _fractionalBits = 8;
};

std::ostream& operator<< (std::ostream& o, Fixed const& i);

#endif
