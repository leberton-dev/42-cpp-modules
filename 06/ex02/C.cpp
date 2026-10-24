#include "C.hpp"

C::C () {
}

C::C (const C& other) {
	(void)other;
}

C& C::operator= (const C& other) {
    if (this != &other) {
    }
    return *this;
}

C::~C () {
}
