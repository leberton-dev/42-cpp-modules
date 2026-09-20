#include "Fixed.hpp"
#include <iostream>

static void testGetRawBits () {
    std::cout << "[ TEST GET RAW BITS ]" << std::endl;
    Fixed a;

    std::cout << a.getRawBits () << std::endl;
}

static void testSetRawBits () {
    std::cout << "[ TEST SET RAW BITS ]" << std::endl;
    Fixed a;

    a.setRawBits (10);
    std::cout << a.getRawBits () << std::endl;
}

static void testDefaultConstructor () {
    std::cout << "[ TEST DEFAULT CONSTRUCTOR ]" << std::endl;

    Fixed a;
}

static void testCopyConstructor () {
    std::cout << "[ TEST COPY CONSTRUCTOR ]" << std::endl;

    Fixed a;
    Fixed b = Fixed (a);
}

static void testCopyAssignementOperator () {
    std::cout << "[ TEST COPY ASSIGNEMENT OPERATOR ]" << std::endl;
    Fixed a;
    Fixed b = a;
}

static void testFloatingPointNumberConstructor () {
    std::cout << "[ TEST FLOATING POINT NUMBER CONSTRUCTOR ]" << std::endl;
    Fixed a (42.42f);
}

static void testIntegerConstructor () {
    std::cout << "[ TEST INTEGER CONSTRUCTOR ]" << std::endl;
    Fixed a (10);
}

static void testStreamOperatorPresent () {
    std::cout << "[ TEST STREAM OPERATOR PRESENT ]" << std::endl;
    Fixed a (42.42f);
    std::cout << a << std::endl;
}

static void testToInt () {
    std::cout << "[ TEST TO INT ]" << std::endl;
    Fixed a;
    a.setRawBits (42);
    std::cout << a.toInt () << std::endl;
}

static void testToFloat () {
    std::cout << "[ TEST TO FLOAT ]" << std::endl;
    Fixed a;
    a.setRawBits (42);
    std::cout << a.toFloat () << std::endl;
}

static void testGreaterThanComparaison () {
    std::cout << "[ TEST GREATER THAN COMPARAISON ]" << std::endl;
    Fixed a;
    Fixed b (10);
    std::cout << (a > b) << std::endl;
}

static void testGreaterEqualThanComparaison () {
    std::cout << "[ TEST GREATER THAN COMPARAISON ]" << std::endl;
    Fixed a;
    Fixed b (10);
    std::cout << (a > b) << std::endl;
}

static void testSmallerThanComparaison () {
    std::cout << "[ TEST SMALLER THAN COMPARAISON ]" << std::endl;
    Fixed a;
    Fixed b (10);
    std::cout << (a < b) << std::endl;
}

static void testSmallerEqualThanComparaison () {
    std::cout << "[ TEST SMALLER EQUAL THAN COMPARAISON ]" << std::endl;
    Fixed a;
    Fixed b (10);
    std::cout << (a < b) << std::endl;
}

static void testEqualsComparaison () {
    std::cout << "[ TEST EQUALS COMPARAISON ]" << std::endl;
    Fixed a (10);
    Fixed b (10);
    std::cout << (a == b) << std::endl;
}

static void testNotEqualsComparaison () {
    std::cout << "[ TEST NOT EQUALS COMPARAISON ]" << std::endl;
    Fixed a (10);
    Fixed b (10);
    std::cout << (a != b) << std::endl;
}

static void testPlusArithmetic () {
    std::cout << "[ TEST PLUS ARITHMETIC ]" << std::endl;
    Fixed a (10);
    Fixed b (10);
    Fixed c = a + b;
    std::cout << c << std::endl;
}

static void testMinusArithmetic () {
    std::cout << "[ TEST MINUS ARITHMETIC ]" << std::endl;
    Fixed a (10);
    Fixed b (10);
    Fixed c = a - b;
    std::cout << c << std::endl;
}

static void testMultiplicationArithmetic () {
    std::cout << "[ TEST MULTIPLICATION ARITHMETIC ]" << std::endl;
    Fixed a (10);
    Fixed b (10);
    Fixed c = a * b;
    std::cout << c << std::endl;
}

static void testDivisionArithmetic () {
    std::cout << "[ TEST DIVISION ARITHMETIC ]" << std::endl;
    Fixed a (10);
    Fixed b (2);
    Fixed c = a / b;
    std::cout << c << std::endl;
}

static void testDivisionByZeroArithmetic () {
    std::cout << "[ TEST DIVISION BY ZERO ARITHMETIC ]" << std::endl;
    Fixed a (10);
    Fixed b (0);
    Fixed c = a / b;
    std::cout << c << std::endl;
}

static void testPreIncrementOperator() { 
    std::cout << "[ TEST PRE INCREMENT OPERATOR ]" << std::endl;
	Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << ++a << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testPostIncrementOperator() { 
    std::cout << "[ TEST POST INCREMENT OPERATOR ]" << std::endl;
	Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << a++ << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testPreDecrementOperator() { 
    std::cout << "[ TEST PRE DECREMENT OPERATOR ]" << std::endl;
	Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << --a << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testPostDecrementOperator() { 
    std::cout << "[ TEST POST DECREMENT OPERATOR ]" << std::endl;
	Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << a-- << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testMinMemberFunction() {
	std::cout << "[ TEST MIN MEMBER FUNCTION ]" << std::endl;
	Fixed a;
	Fixed b (42);
	std::cout << Fixed::min(a, b) << std::endl;
}

static void testMaxMemberFunction() {
	std::cout << "[ TEST MAX MEMBER FUNCTION ]" << std::endl;
	Fixed a;
	Fixed b (42);
	std::cout << Fixed::max(a, b) << std::endl;
}


int main (void) {
    testGetRawBits ();
    testSetRawBits ();
    testDefaultConstructor ();
    testCopyConstructor ();
    testCopyAssignementOperator ();

    testFloatingPointNumberConstructor ();
    testIntegerConstructor ();
    testStreamOperatorPresent ();
    testToInt ();
    testToFloat ();

    testGreaterThanComparaison ();
    testGreaterEqualThanComparaison ();
    testSmallerThanComparaison ();
    testSmallerEqualThanComparaison ();
    testEqualsComparaison ();
    testNotEqualsComparaison ();

    testPlusArithmetic ();
    testMinusArithmetic ();
    testMultiplicationArithmetic ();
    testDivisionArithmetic ();
	testDivisionByZeroArithmetic();

	testPreIncrementOperator();
	testPostIncrementOperator();
	testPreDecrementOperator();
	testPostDecrementOperator();

	testMinMemberFunction();
	testMaxMemberFunction();

    // Fixed a;
    // Fixed const b (Fixed (5.05f) * Fixed (2));
    //
    // std::cout << a << std::endl;
    // std::cout << ++a << std::endl;
    // std::cout << a << std::endl;
    // std::cout << a++ << std::endl;
    // std::cout << a << std::endl;
    // std::cout << b << std::endl;
    // std::cout << Fixed::max (a, b) << std::endl;
    //
    // return 0;
}
