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

    printTestTitle ("TEST IN SUBJECT");
    Fixed a;
    Fixed const b (10);
    Fixed const c (42.42f);
    Fixed const d (b);

    a = Fixed (1234.4321f);

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    std::cout << "a is " << a.toInt () << " as integer" << std::endl;
    std::cout << "b is " << b.toInt () << " as integer" << std::endl;
    std::cout << "c is " << c.toInt () << " as integer" << std::endl;
    std::cout << "d is " << d.toInt () << " as integer" << std::endl;

    return 0;
}
