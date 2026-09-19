#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include <string>

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

#define DIAMONDTRAP_HP FRAGTRAP_HP
#define DIAMONDTRAP_EP SCAVTRAP_EP
#define DIAMONDTRAP_AD FRAGTRAP_AD

class DiamondTrap : public ScavTrap, public FragTrap {
    public:
    DiamondTrap ();
    DiamondTrap (std::string name);
    DiamondTrap (const DiamondTrap& other);
    DiamondTrap& operator= (const DiamondTrap& other);
    ~DiamondTrap ();

    using ScavTrap::attack;
	void whoAmI();

    private:
    std::string _name;
};

#endif
