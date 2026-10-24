#include "A.hpp"

A::A () {
}

A::A (const A& other) {
	(void)other;
}

A& A::operator= (const A& other) {
	if (this != &other) {
	}
	return *this;
}

A::~A () {
}
