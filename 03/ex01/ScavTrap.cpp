#include "ScavTrap.hpp"

#include <iostream>
#include <sstream>

static void
_logEnterConstructor (std::string name, std::string constructor_type, std::string color) {
    std::cout << "Entering " << color << "ScavTrap " << name << RESET << " "
              << constructor_type << std::endl;
}

static void
_logActionSuccess (const std::string& action, const std::string& color, std::string& name) {
    std::cout << color << "ScavTrap " << name << RESET << " " << action << std::endl;
}

static void _logActionFailed (const std::string& action,
const std::string& reason,
const std::string& color,
const std::string& name) {
    std::cout << color << "ScavTrap " << name << RESET << " cannot " << action
              << " due to " << reason << std::endl;
}

static std::string _combineStringAndInt (std::string str, int a) {
    std::stringstream ss;
    ss << a;
    return str + ss.str ();
}

ScavTrap::ScavTrap () {
    _logEnterConstructor (_name, "default constructor", GREEN);
    _hitPoints    = HP;
    _energyPoints = EP;
    _attackDamage = AD;
}

ScavTrap::ScavTrap (std::string name) : ClapTrap (name) {
    _logEnterConstructor (_name, "parameterized constructor", GREEN);
    _hitPoints    = HP;
    _energyPoints = EP;
    _attackDamage = AD;
}

ScavTrap::ScavTrap (const ScavTrap& other) : ClapTrap (other) {
    _logEnterConstructor (_name, "copy constructor. Copying from " + other._name, GREEN);
    _hitPoints    = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
}

ScavTrap& ScavTrap::operator= (const ScavTrap& other) {
    _logEnterConstructor (
    _name, "copy assignment constructor. Copying from " + other._name, GREEN);
    if (this != &other) {
        _name         = other._name;
        _hitPoints    = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    return (*this);
}

ScavTrap::~ScavTrap () {
    _logEnterConstructor (_name, "destructor", GREEN);
}

void ScavTrap::attack (const std::string& target) {
    std::string action;

    if (_energyPoints > 0 && _hitPoints > 0) {
        _energyPoints--;
        action = _combineStringAndInt ("attacks " + target + ", causing ", _attackDamage);
        action += " points of damage!";
        action += _combineStringAndInt (" Current energy points: ", _energyPoints);
        _logActionSuccess (action, GREEN, _name);
    } else if (_energyPoints <= 0 && _hitPoints <= 0)
        _logActionFailed ("attack", "insufficient energy and hit points", YELLOW, _name);
    else if (_energyPoints <= 0)
        _logActionFailed ("attack", "insufficient energy points", YELLOW, _name);
    else
        _logActionFailed ("attack", "insufficient hit points", YELLOW, _name);
}

void ScavTrap::guardGate () {
    _logActionSuccess ("is in guard gate mode", GREEN, _name);
}
