#include <cstdlib>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

Base::Base () {
}

Base::~Base () {
}

Base* generate (void) {
    int choice = std::rand () % 3;

    switch (choice) {
    case 0: return new A ();
    case 1: return new B ();
    case 2: return new C ();
    }

    return NULL;
}

void identify (Base* p) {
    if (dynamic_cast<A*> (p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*> (p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*> (p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

void identify (Base& p) {
    try {
        (void)dynamic_cast<A&> (p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::exception&) {
    }

    try {
        (void)dynamic_cast<B&> (p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::exception&) {
    }

    try {
        (void)dynamic_cast<C&> (p);
        std::cout << "C" << std::endl;
        return;
    } catch (std::exception&) {
    }

    std::cout << "Unknown type" << std::endl;
}
