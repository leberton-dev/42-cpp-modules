#include "whatever.hpp"

#include <iostream>

int main (void) {
    int a = 2;
    int b = 3;
    ::swap (a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min(a, b) = " << ::min (a, b) << std::endl;
    std::cout << "max(a, b) = " << ::max (a, b) << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap (c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min(c, d) = " << ::min (c, d) << std::endl;
    std::cout << "max(c, d) = " << ::max (c, d) << std::endl;

    int x = 5;
    int y = 5;
    std::cout << (&::min (x, y) == &y) << std::endl;
    std::cout << (&::max (x, y) == &y) << std::endl;

    float fa = 6.9f;
    float fb = 4.2f;
    ::swap (fa, fb);
    std::cout << "fa = " << fa << ", fb = " << fb << std::endl;
    std::cout << "min(fa, fb) = " << ::min (fa, fb) << std::endl;
    std::cout << "max(fa, fb) = " << ::max (fa, fb) << std::endl;

    char ca = 'Z';
    char cb = 'A';
    ::swap (ca, cb);
    std::cout << "ca = " << ca << ", cb = " << cb << std::endl;
    std::cout << "min(ca, cb) = " << ::min (ca, cb) << std::endl;
    std::cout << "max(ca, cb) = " << ::max (ca, cb) << std::endl;

    ::max (a, b) = 42;
    std::cout << "::max(a, b) = 42 -> a = " << a << std::endl;
    ::min (a, b) = 13;
    std::cout << "::min(a, b) = 13 -> b = " << b << std::endl;

    return 0;
}
