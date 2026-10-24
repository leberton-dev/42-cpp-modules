#include "B.hpp"

B::B () {
}

B::B (const B& other) {
	(void)other;
}

B& B::operator= (const B& other) {
    if (this != &other) {
    }
    return *this;
}

B::~B () {
}
