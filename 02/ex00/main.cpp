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

int main (void) {
    testGetRawBits ();
    testSetRawBits ();
    testDefaultConstructor ();
    testCopyConstructor ();
    testCopyAssignementOperator ();

    printTestTitle ("TEST IN SUBJECT");
    Fixed a;
    Fixed b (a);
    Fixed c;
    c = b;
    std::cout << a.getRawBits () << std::endl;
    std::cout << b.getRawBits () << std::endl;
    std::cout << c.getRawBits () << std::endl;

    return 0;
}
