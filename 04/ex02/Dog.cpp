#include <iostream>

#include "Dog.hpp"


Dog::Dog () : AAnimal ("Dog") {
    std::cout << "Entered Dog default constructor" << std::endl;
	this->brain = new Brain;
}

Dog::Dog (const Dog& other) : AAnimal (other.type) {
    std::cout << "Entered Dog copy constructor" << std::endl;
	this->brain = new Brain(*other.brain);
}

Dog& Dog::operator= (const Dog& other) {
    std::cout << "Entered Dog copy assignment constructor" << std::endl;
    if (this != &other) {
        this->type = other.type;
		*this->brain = *other.brain;
	}
    return (*this);
}

Dog::~Dog () {
    std::cout << "Entered Dog deconstructor" << std::endl;
	delete this->brain;
}

void Dog::makeSound() const {
	std::cout << "Wuaff" << std::endl;
}

Brain* Dog::getBrain() const {
	return this->brain;
}
