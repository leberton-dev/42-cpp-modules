#include "WrongCat.hpp"

#include <iostream>


WrongCat::WrongCat () : WrongAnimal ("WrongCat") {
    std::cout << "Entered WrongCat default constructor" << std::endl;
};

WrongCat::WrongCat (const std::string& type) : WrongAnimal (type) {
    std::cout << "Entered WrongCat parameterized constructor" << std::endl;
}

WrongCat::WrongCat (const WrongCat& other) : WrongAnimal (other) {
    std::cout << "Entered WrongCat copy constructor" << std::endl;
}

WrongCat WrongCat::operator= (const WrongCat& other) {
    std::cout << "Entered WrongCat copy assignment constructor" << std::endl;
    if (this != &other)
        type = other.type;
    return (*this);
}

WrongCat::~WrongCat () {
    std::cout << "Entered WrongCat destructor" << std::endl;
}

void WrongCat::makeSound () const {
    std::cout << "Wrong Miauw" << std::endl;
}
