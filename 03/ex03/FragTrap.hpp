#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

#define RED "\033[1;31m"
#define RESET "\033[0m"

#define FRAGTRAP_HP 100
#define FRAGTRAP_EP 100
#define FRAGTRAP_AD 30

class FragTrap : virtual public ClapTrap {
    public:
    FragTrap ();
    FragTrap (std::string name);
    FragTrap (const FragTrap& other);
    FragTrap& operator= (const FragTrap& other);
    ~FragTrap ();

	void highFivesGuys(void);
};

#endif
