#include "DiamondTrap.hpp"

#include <iostream>

static void
_logEnterConstructor (std::string name, std::string constructor_type, std::string color) {
    std::cout << "Entering " << color << "DiamondTrap " << name << RESET << " "
              << constructor_type << std::endl;
}

DiamondTrap::DiamondTrap ()
: ClapTrap ("default_clap_name"), _name ("default") {
    _logEnterConstructor (_name, "default constructor", MAGENTA);
    _hitPoints    = DIAMONDTRAP_HP;
    _energyPoints = DIAMONDTRAP_EP;
    _attackDamage = DIAMONDTRAP_AD;
}

DiamondTrap::DiamondTrap (std::string name)
: ClapTrap (name + "_clap_name"), ScavTrap (name), FragTrap (name), _name (name) {
    _logEnterConstructor (_name, "parameterized constructor", MAGENTA);
    _hitPoints    = DIAMONDTRAP_HP;
    _energyPoints = DIAMONDTRAP_EP;
    _attackDamage = DIAMONDTRAP_AD;
}

DiamondTrap::DiamondTrap (const DiamondTrap& other)
: ClapTrap (other), ScavTrap (other), FragTrap (other), _name (other._name) {
    _logEnterConstructor (_name, "copy constructor. Copying from " + other._name, MAGENTA);
    _hitPoints    = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
}

DiamondTrap& DiamondTrap::operator= (const DiamondTrap& other) {
    _logEnterConstructor (
    _name, "copy assignment constructor. Copying from " + other._name, MAGENTA);
    if (this != &other) {
        ClapTrap::_name = other.ClapTrap::_name;
        _name           = other._name;
        _hitPoints      = other._hitPoints;
        _energyPoints   = other._energyPoints;
        _attackDamage   = other._attackDamage;
    }
    return (*this);
}


DiamondTrap::~DiamondTrap () {
    _logEnterConstructor (_name, "destructor", MAGENTA);
}

void DiamondTrap::whoAmI () {
    std::cout << "My name:   " << MAGENTA << _name << RESET << std::endl;
    std::cout << "Base name: " << MAGENTA << ClapTrap::_name << RESET << std::endl;
}
