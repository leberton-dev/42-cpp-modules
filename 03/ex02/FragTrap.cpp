#include "FragTrap.hpp"


#include <iostream>

static void
_logEnterConstructor (std::string name, std::string constructor_type, std::string color) {
    std::cout << "Entering " << color << "FragTrap " << name << RESET << " "
              << constructor_type << std::endl;
}

static void
_logActionSuccess (const std::string& action, const std::string& color, std::string& name) {
    std::cout << color << "FragTrap " << name << RESET << " " << action << std::endl;
}

FragTrap::FragTrap () {
    _logEnterConstructor (_name, "default constructor", RED);
    _hitPoints    = FRAGTRAP_HP;
    _energyPoints = FRAGTRAP_EP;
    _attackDamage = FRAGTRAP_AD;
}

FragTrap::FragTrap (std::string name) : ClapTrap (name) {
    _logEnterConstructor (_name, "parameterized constructor", RED);
    _hitPoints    = FRAGTRAP_HP;
    _energyPoints = FRAGTRAP_EP;
    _attackDamage = FRAGTRAP_AD;
}

FragTrap::FragTrap (const FragTrap& other) : ClapTrap (other) {
    _logEnterConstructor (_name, "copy constructor. Copying from " + other._name, RED);
    _hitPoints    = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
}

FragTrap& FragTrap::operator= (const FragTrap& other) {
    _logEnterConstructor (
    _name, "copy assignment constructor. Copying from " + other._name, RED);
    if (this != &other) {
        _name         = other._name;
        _hitPoints    = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    return (*this);
}

FragTrap::~FragTrap () {
    _logEnterConstructor (_name, "destructor", RED);
}

void FragTrap::highFivesGuys (void) {
    _logActionSuccess ("requested high-fives guys", RED, _name);
}
