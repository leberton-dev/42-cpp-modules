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

int main (void) {
	testGetRawBits();
	testSetRawBits();
	testDefaultConstructor();
	testCopyConstructor();
	testCopyAssignementOperator();
    return 0;
}
