#include "WrongAnimal.hpp"

#include <iostream>

WrongAnimal::WrongAnimal () : type ("WrongAnimal") {
	std::cout << "Entered WrongAnimal default constructor" << std::endl;
}

WrongAnimal::WrongAnimal (const std::string& type) : type (type) {
	std::cout << "Entered WrongAnimal parameterized constructor" << std::endl;
}

WrongAnimal::WrongAnimal (const WrongAnimal& other) : type (other.type) {
	std::cout << "Entered WrongAnimal copy constructor" << std::endl;
}

WrongAnimal WrongAnimal::operator= (const WrongAnimal& other) {
	std::cout << "Entered WrongAnimal copy assignment constructor" << std::endl;
    if (this != &other) {
        type = other.type;
    }
    return (*this);
}

WrongAnimal::~WrongAnimal () {
	std::cout << "Entered WrongAnimal destructor" << std::endl;
}


const std::string WrongAnimal::getType () const {
    return type;
}

void WrongAnimal::makeSound () const {
    std::cout << "WrongAnimalSound" << std::endl;
}
