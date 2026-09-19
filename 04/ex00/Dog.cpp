#include <iostream>

#include "Dog.hpp"


Dog::Dog () : Animal ("Dog") {
    std::cout << "Entered Dog default constructor" << std::endl;
}

Dog::Dog (const std::string& type) : Animal (type) {
    std::cout << "Entered Dog parameterized constructor" << std::endl;
}

Dog::Dog (const Dog& other) : Animal (other.type) {
    std::cout << "Entered Dog copy constructor" << std::endl;
}

Dog& Dog::operator= (const Dog& other) {
    std::cout << "Entered Dog copy assignment constructor" << std::endl;
    if (this != &other)
        type = other.type;
    return (*this);
}

Dog::~Dog () {
    std::cout << "Entered Dog deconstructor" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Wuaff" << std::endl;
}
