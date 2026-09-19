#include <iostream>

#include "Animal.hpp"

Animal::Animal () : type ("Animal") {
    std::cout << "Entered Animal default constructor" << std::endl;
}

Animal::Animal (const std::string& type) : type (type) {
    std::cout << "Entered Animal parameterized constructor" << std::endl;
}

Animal::Animal (const Animal& other) : type (other.type) {
    std::cout << "Entered Animal copy constructor" << std::endl;
}

Animal& Animal::operator= (const Animal& other) {
    if (this != &other)
        type = other.type;
    return (*this);
}

Animal::~Animal () {
    std::cout << "Entered Animal object deconstructor" << std::endl;
}

void Animal::makeSound() const {
	std::cout << "Animal noise" << std::endl;
}

const std::string& Animal::getType() const {
	return type;
}
