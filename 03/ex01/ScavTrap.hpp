#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

#define HP 100
#define EP 50
#define AD 20

class ScavTrap : public ClapTrap {
    public:
    ScavTrap ();
    ScavTrap (std::string name);
    ScavTrap (const ScavTrap& other);
    ScavTrap& operator= (const ScavTrap& other);
    ~ScavTrap ();

    void attack (const std::string& target);
	void guardGate();
};

#endif
