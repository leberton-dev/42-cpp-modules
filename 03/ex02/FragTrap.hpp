#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

#define RED "\033[1;31m"
#define RESET "\033[0m"

#define HP 100
#define EP 100
#define AD 30

class FragTrap : public ClapTrap {
    public:
    FragTrap ();
    FragTrap (std::string name);
    FragTrap (const FragTrap& other);
    FragTrap& operator= (const FragTrap& other);
    ~FragTrap ();

	void highFivesGuys(void);
};

#endif
