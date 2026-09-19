#include <iostream>

#include "AAnimal.hpp"

AAnimal::AAnimal () : type ("Animal") {
    std::cout << "Entered AAnimal default constructor" << std::endl;
}

AAnimal::AAnimal (const std::string& type) : type (type) {
    std::cout << "Entered AAnimal parameterized constructor" << std::endl;
}

AAnimal::AAnimal (const AAnimal& other) : type (other.type) {
    std::cout << "Entered AAnimal copy constructor" << std::endl;
}

AAnimal& AAnimal::operator= (const AAnimal& other) {
    if (this != &other)
        type = other.type;
    return (*this);
}

AAnimal::~AAnimal () {
    std::cout << "Entered AAnimal object deconstructor" << std::endl;
}

const std::string& AAnimal::getType() const {
	return type;
}
