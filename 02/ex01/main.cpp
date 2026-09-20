#include "Fixed.hpp"
#include <iostream>

static void testGetRawBits() {
	std::cout << "[ TEST GET RAW BITS ]" << std::endl;
	Fixed a;

	std::cout << a.getRawBits() << std::endl;
}

static void testSetRawBits() {
	std::cout << "[ TEST SET RAW BITS ]" << std::endl;
	Fixed a;

	a.setRawBits(10);
	std::cout << a.getRawBits() << std::endl;
}

static void testDefaultConstructor() {
	std::cout << "[ TEST DEFAULT CONSTRUCTOR ]" << std::endl;

	Fixed a;
}

static void testCopyConstructor() {
	std::cout << "[ TEST COPY CONSTRUCTOR ]" << std::endl;

	Fixed a;
	Fixed b = Fixed(a);
}

static void testCopyAssignementOperator() {
	std::cout << "[ TEST COPY ASSIGNEMENT OPERATOR ]" << std::endl;
	Fixed a;
	Fixed b = a;
}

static void testFloatingPointNumberConstructor() {
	std::cout << "[ TEST FLOATING POINT NUMBER CONSTRUCTOR ]" << std::endl;
	Fixed a (42.42f);
}

static void testIntegerConstructor() {
	std::cout << "[ TEST INTEGER CONSTRUCTOR ]" << std::endl;
	Fixed a (10);
}

static void testStreamOperatorPresent() {
	std::cout << "[ TEST STREAM OPERATOR PRESENT ]" << std::endl;
	Fixed a (42.42f);
	std::cout << a << std::endl;
}

static void testToInt() {
	std::cout << "[ TEST TO INT ]" << std::endl;
	Fixed a;
	a.setRawBits(42);
	std::cout << a.toInt() << std::endl;
}

static void testToFloat() {
	std::cout << "[ TEST TO FLOAT ]" << std::endl;
	Fixed a;
	a.setRawBits(42);
	std::cout << a.toFloat() << std::endl;
}

int main (void) {
	testGetRawBits();
	testSetRawBits();
	testDefaultConstructor();
	testCopyConstructor();
	testCopyAssignementOperator();
	testFloatingPointNumberConstructor();
	testIntegerConstructor();
	testStreamOperatorPresent();
	testToInt();
	testToFloat();

    // Fixed a;
    // Fixed const b (10);
    // Fixed const c (42.42f);
    // Fixed const d (b);
    //
    // a = Fixed (1234.4321f);
    //
    // std::cout << "a is " << a << std::endl;
    // std::cout << "b is " << b << std::endl;
    // std::cout << "c is " << c << std::endl;
    // std::cout << "d is " << d << std::endl;
    // std::cout << "a is " << a.toInt () << " as integer" << std::endl;
    // std::cout << "b is " << b.toInt () << " as integer" << std::endl;
    // std::cout << "c is " << c.toInt () << " as integer" << std::endl;
    // std::cout << "d is " << d.toInt () << " as integer" << std::endl;
    //
    return 0;
}
