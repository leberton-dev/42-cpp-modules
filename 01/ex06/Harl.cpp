#include "Harl.hpp"

#include <iostream>

Harl::Harl () {
}
Harl::~Harl () {
}

void Harl::complain (int start) {
    std::string const lvls[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    void (Harl::* ptrFunc[4]) (
    void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
    for (int i = start; i < 4; i++) {
        (this->*ptrFunc[i]) ();
        std::cout << std::endl;
    }
}

void Harl::complainFilter (std::string level) {
    std::string const lvls[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    int i                     = 0;
    while (i < 4 && lvls[i] != level)
        i++;
    switch (i) {
    case 0: this->complain (i); break;
    case 1: this->complain (i); break;
    case 2: this->complain (i); break;
    case 3: this->complain (i); break;
    }
}

void Harl::debug (void) {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout
    << "I love having extra bacon for my "
       "7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
    << std::endl;
}

void Harl::info (void) {
    std::cout << "[ INFO ]" << std::endl;
    std::cout
    << "I cannot believe adding extra bacon costs more money. You didn’t put "
       "enough bacon in my burger! If you did, I wouldn’t be asking for more!"
    << std::endl;
}

void Harl::warning (void) {
    std::cout << "[ WARNING ]" << std::endl;
    std::cout
    << "I think I deserve to have some extra bacon for free. I’ve been "
       "coming for years, whereas you started working here just last month."
    << std::endl;
}

void Harl::error (void) {
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}
