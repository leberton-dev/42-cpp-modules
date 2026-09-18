#include "ClapTrap.hpp"

#include <iostream>
#include <sstream>

static void _logEnterConstructor (std::string name, std::string constructor_type, std::string color) {
    std::cout << "Entering " << color << "ClapTrap " << name << RESET << " "
              << constructor_type << std::endl;
}

static void _logActionSuccess (const std::string& action, const std::string& color, std::string& name) {
    std::cout << color << "ClapTrap " << name << RESET << " " << action << std::endl;
}

static void _logActionFailed (const std::string& action,
const std::string& reason,
const std::string& color,
const std::string& name) {
    std::cout << color << "ClapTrap " << name << RESET << " cannot " << action
              << " due to " << reason << std::endl;
}

static std::string _combineStringAndInt (std::string str, int a) {
    std::stringstream ss;
    ss << a;
    return str + ss.str ();
}

static int _max (int a, int b) {
    if (b > a)
        return b;
    return a;
}

ClapTrap::ClapTrap ()
: _name ("default"), _hitPoints (10), _energyPoints (10), _attackDamage (0) {
    _logEnterConstructor (_name, "default constructor", BLUE);
}

ClapTrap::ClapTrap (std::string name)
: _name (name.empty () ? "default" : name), _hitPoints (10), _energyPoints (10),
  _attackDamage (0) {
    _logEnterConstructor (_name, "parameterized constructor", BLUE);
}

ClapTrap::ClapTrap (const ClapTrap& other)
: _name (other._name), _hitPoints (other._hitPoints),
  _energyPoints (other._energyPoints), _attackDamage (other._attackDamage) {
    _logEnterConstructor (_name, "copy constructor. Copying from " + other._name, BLUE);
}

ClapTrap& ClapTrap::operator= (const ClapTrap& other) {
    _logEnterConstructor (
    _name, "copy assignment constructor. Copying from " + other._name, BLUE);
    if (this != &other) {
        _name         = other._name;
        _hitPoints    = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    return (*this);
}

ClapTrap::~ClapTrap () {
    _logEnterConstructor (_name, "destructor", BLUE);
}

void ClapTrap::attack (const std::string& target) {
    std::string action;

    if (_energyPoints > 0 && _hitPoints > 0) {
        _energyPoints--;
        action = _combineStringAndInt ("attacks " + target + ", causing ", _attackDamage);
        action += " points of damage!";
        action += _combineStringAndInt (" Current energy points: ", _energyPoints);
        _logActionSuccess (action, BLUE, _name);
    } else if (_energyPoints <= 0 && _hitPoints <= 0)
        _logActionFailed ("attack", "insufficient energy and hit points", YELLOW, _name);
    else if (_energyPoints <= 0)
        _logActionFailed ("attack", "insufficient energy points", YELLOW, _name);
    else
        _logActionFailed ("attack", "insufficient hit points", YELLOW, _name);
}

void ClapTrap::takeDamage (const unsigned int amount) {
    std::string action = "";
    if (_hitPoints > 0) {
        _hitPoints = _max (_hitPoints - amount, 0);
        action += _combineStringAndInt ("took ", amount);
        action += _combineStringAndInt (" of damage. Remaining hitPoints: ", _hitPoints);
        _logActionSuccess (action, BLUE, _name);
    } else
        _logActionFailed ("take damage", "insufficient hit points", YELLOW, _name);
}

void ClapTrap::beRepaired (const unsigned int amount) {
    std::string action = "";

    if (_energyPoints > 0 && _hitPoints > 0) {
        _hitPoints += amount;
        _energyPoints--;
        action += _combineStringAndInt ("repairs itself for ", amount);
        action += _combineStringAndInt ("! Current hit points: ", _hitPoints);
        action += _combineStringAndInt (", energy points: ", _energyPoints);
        _logActionSuccess (action, BLUE, _name);
    } else if (_energyPoints <= 0 && _hitPoints <= 0)
        _logActionFailed (
        "repair himself", "insufficient energy and hit points", YELLOW, _name);
    else if (_energyPoints <= 0)
        _logActionFailed ("repair himself", "insufficient energy points", YELLOW, _name);
    else
        _logActionFailed ("repair himself", "insufficient hit points", YELLOW, _name);
}

void ClapTrap::log (void) {
    std::cout << BLUE << "ClapTrap " << _name << RESET << ":" << std::endl;
    std::cout << "-HP: " << _hitPoints << std::endl;
    std::cout << "-EP: " << _energyPoints << std::endl;
    std::cout << "-AD: " << _attackDamage << std::endl;
}
