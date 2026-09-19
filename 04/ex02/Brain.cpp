#include "Brain.hpp"

#include <iostream>

Brain::Brain () {
    std::cout << "Entered Brain default constructor" << std::endl;
}

Brain::Brain (const Brain& other) {
    std::cout << "Entered Brain copy constructor" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = other.ideas[i];
}

Brain& Brain::operator= (const Brain& other) {
    std::cout << "Entered Brain copy assignement constructor" << std::endl;
    if (this != &other) {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return (*this);
}

Brain::~Brain () {
    std::cout << "Entered Brain destructor" << std::endl;
}
