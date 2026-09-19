#include <iostream>

#include "Cat.hpp"


Cat::Cat () : Animal ("Cat") {
    std::cout << "Entered Cat default constructor" << std::endl;
    this->brain = new Brain;
}

Cat::Cat (const Cat& other) : Animal (other.type) {
    std::cout << "Entered Cat copy constructor" << std::endl;
    this->brain = new Brain(*other.brain);
}

Cat& Cat::operator= (const Cat& other) {
    std::cout << "Entered Cat copy assignment constructor" << std::endl;
    if (this != &other) {
        this->type   = other.type;
        *this->brain = *other.brain;
    }
    return (*this);
}

Cat::~Cat () {
    std::cout << "Entered Cat deconstructor" << std::endl;
    delete this->brain;
}

void Cat::makeSound () const {
    std::cout << "Miaow" << std::endl;
}

Brain* Cat::getBrain () const {
    return this->brain;
}
