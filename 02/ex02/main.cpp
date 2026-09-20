#include "Fixed.hpp"
#include <iostream>

static void printTestTitle (const std::string& title) {
    std::cout << std::endl << "[ " << title << " ]" << std::endl;
}

static void testGetRawBits () {
    printTestTitle ("TEST GET RAW BITS");

    Fixed a;
    std::cout << a.getRawBits () << std::endl;
}

static void testSetRawBits () {
    printTestTitle ("TEST SET RAW BITS");
    Fixed a;

    a.setRawBits (10);
    std::cout << a.getRawBits () << std::endl;
}

static void testDefaultConstructor () {
    printTestTitle ("TEST DEFAULT CONSTRUCTOR");

    Fixed a;
}

static void testCopyConstructor () {
    printTestTitle ("TEST COPY CONSTRUCTOR");

    Fixed a;
    Fixed b = Fixed (a);
}

static void testCopyAssignementOperator () {
    printTestTitle ("TEST COPY ASSIGNEMENT OPERATOR");
    Fixed a;
    Fixed b = a;
}

static void testFloatingPointNumberConstructor () {
    printTestTitle ("TEST FLOATING POINT NUMBER CONSTRUCTOR");
    Fixed a (42.42f);
}

static void testIntegerConstructor () {
    printTestTitle ("TEST INTEGER CONSTRUCTOR");
    Fixed a (10);
}

static void testStreamOperatorPresent () {
    printTestTitle ("TEST STREAM OPERATOR PRESENT");
    Fixed a (42.42f);
    std::cout << a << std::endl;
}

static void testToInt () {
    printTestTitle ("TEST TO INT");
    Fixed a;
    a.setRawBits (42);
    std::cout << a.toInt () << std::endl;
}

static void testToFloat () {
    printTestTitle ("TEST TO FLOAT");
    Fixed a;
    a.setRawBits (42);
    std::cout << a.toFloat () << std::endl;
}

static void testGreaterThanComparaison () {
    printTestTitle ("TEST GREATER THAN COMPARAISON");
    Fixed a;
    Fixed b (10);
    Fixed c;
    std::cout << (a > b) << std::endl;
    std::cout << (a > c) << std::endl;
}

static void testGreaterEqualThanComparaison () {
    printTestTitle ("TEST GREATER EQUAL THAN COMPARAISON");
    Fixed a;
    Fixed b (10);
    Fixed c;
    std::cout << (a >= b) << std::endl;
    std::cout << (a >= c) << std::endl;
}

static void testSmallerThanComparaison () {
    printTestTitle ("TEST SMALLER THAN COMPARAISON");
    Fixed a;
    Fixed b (10);
    Fixed c;
    std::cout << (a < b) << std::endl;
    std::cout << (a < c) << std::endl;
}

static void testSmallerEqualThanComparaison () {
    printTestTitle ("TEST SMALLER EQUAL THAN COMPARAISON");
    Fixed a;
    Fixed b (10);
    Fixed c;
    std::cout << (a <= b) << std::endl;
    std::cout << (a <= c) << std::endl;
}

static void testEqualsComparaison () {
    printTestTitle ("TEST EQUALS COMPARAISON");
    Fixed a (10);
    Fixed b (10);
    Fixed c;
    std::cout << (a == b) << std::endl;
    std::cout << (a == c) << std::endl;
}

static void testNotEqualsComparaison () {
    printTestTitle ("TEST NOT EQUALS COMPARAISON");
    Fixed a (10);
    Fixed b (10);
    Fixed c;
    std::cout << (a != b) << std::endl;
    std::cout << (a != c) << std::endl;
}

static void testPlusArithmetic () {
    printTestTitle ("TEST PLUS ARITHMETIC");
    Fixed a (10);
    Fixed b (10);
    Fixed c = a + b;
    std::cout << c << std::endl;

    Fixed d (42.42f);
    Fixed e (0.58f);
    Fixed f = d + e;
    std::cout << f << std::endl;
}

static void testMinusArithmetic () {
    printTestTitle ("TEST MINUS ARITHMETIC");
    Fixed a (10);
    Fixed b (10);
    Fixed c = a - b;
    std::cout << c << std::endl;

    Fixed d (42.42f);
    Fixed e (0.42f);
    Fixed f = d - e;
    std::cout << f << std::endl;
}

static void testMultiplicationArithmetic () {
    printTestTitle ("TEST MULTIPLICATION ARITHMETIC");
    Fixed a (10);
    Fixed b (10);
    Fixed c = a * b;
    std::cout << c << std::endl;

    Fixed d (42.42f);
    Fixed e (0.58f);
    Fixed f = d * e;
    std::cout << f << std::endl;
}

static void testDivisionArithmetic () {
    printTestTitle ("TEST DIVISION ARITHMETIC");
    Fixed a (10);
    Fixed b (2);
    Fixed c = a / b;
    std::cout << c << std::endl;

    Fixed d (42.42f);
    Fixed e (0.58f);
    Fixed f = d / e;
    std::cout << f << std::endl;
}

static void testDivisionByZeroArithmetic () {
    printTestTitle ("TEST DIVISION BY ZERO ARITHMETIC");
    Fixed a (10);
    Fixed b (0);
    Fixed c = a / b;
    std::cout << c << std::endl;
}

static void testPreIncrementOperator () {
    printTestTitle ("TEST PRE INCREMENT OPERATOR");
    Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << ++a << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testPostIncrementOperator () {
    printTestTitle ("TEST POST INCREMENT OPERATOR");
    Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << a++ << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testPreDecrementOperator () {
    printTestTitle ("TEST PRE DECREMENT OPERATOR");
    Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << --a << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testPostDecrementOperator () {
    printTestTitle ("TEST POST DECREMENT OPERATOR");
    Fixed a;
    std::cout << "Before: " << a << std::endl;
    std::cout << "During: " << a-- << std::endl;
    std::cout << "After:  " << a << std::endl;
}

static void testMinMemberFunction () {
    printTestTitle ("TEST MIN MEMBER FUNCTION");
    Fixed a;
    Fixed b (42);
    std::cout << Fixed::min (a, b) << std::endl;
    Fixed::min (a, b) = Fixed (7);
    std::cout << a << std::endl;
}

static void testMaxMemberFunction () {
    printTestTitle ("TEST MAX MEMBER FUNCTION");
    Fixed a;
    Fixed b (42);
    std::cout << Fixed::max (a, b) << std::endl;
    Fixed::max (a, b) = Fixed (7);
    std::cout << a << std::endl;
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
    testDivisionByZeroArithmetic ();

    testPreIncrementOperator ();
    testPostIncrementOperator ();
    testPreDecrementOperator ();
    testPostDecrementOperator ();

    testMinMemberFunction ();
    testMaxMemberFunction ();

    printTestTitle ("TEST IN SUBJECT");
    Fixed a;
    Fixed const b (Fixed (5.05f) * Fixed (2));

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max (a, b) << std::endl;

    return 0;
}
