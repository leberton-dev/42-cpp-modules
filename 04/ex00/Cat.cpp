#include <iostream>

#include "Cat.hpp"


Cat::Cat(): Animal("Cat") {
	std::cout << "Entered Cat default constructor" << std::endl;
}

Cat::Cat (const Cat& other) : Animal (other.type) {
    std::cout << "Entered Cat copy constructor" << std::endl;
}

Cat& Cat::operator= (const Cat& other) {
    std::cout << "Entered Cat copy assignment constructor" << std::endl;
    if (this != &other)
        type = other.type;
    return (*this);
}

Cat::~Cat() {
	std::cout << "Entered Cat deconstructor" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Miaow" << std::endl;
}
