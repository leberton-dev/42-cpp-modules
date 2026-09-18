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

    bool operator== (const Fixed& rhs) const;
    bool operator!= (const Fixed& rhs) const;
    bool operator< (const Fixed& rhs) const;
    bool operator> (const Fixed& rhs) const;
    bool operator<= (const Fixed& rhs) const;
    bool operator>= (const Fixed& rhs) const;

    Fixed operator+ (const Fixed& rhs) const;
    Fixed operator- (const Fixed& rhs) const;
    Fixed operator* (const Fixed& rhs) const;
    Fixed operator/ (const Fixed& rhs) const;

    Fixed& operator++ ();
    Fixed operator++ (int);
    Fixed& operator-- ();
    Fixed operator-- (int);

    int getRawBits (void) const;
    void setRawBits (int const raw);
    float toFloat (void) const;
    int toInt (void) const;
    static Fixed& min (Fixed& a, Fixed& b);
    static const Fixed& min (const Fixed& a, const Fixed& b);
    static Fixed& max (Fixed& a, Fixed& b);
    static const Fixed& max (const Fixed& a, const Fixed& b);

    private:
    int _value;
    static const int _fractionalBits = 8;
};

std::ostream& operator<< (std::ostream& o, Fixed const& i);

#endif
