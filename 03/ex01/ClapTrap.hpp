#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

class ClapTrap {
    public:
    ClapTrap ();
    ClapTrap (std::string name);
    ClapTrap (const ClapTrap& other);
    ClapTrap& operator= (const ClapTrap& other);
    ~ClapTrap ();

    void attack (const std::string& target);
    void takeDamage (unsigned int amount);
    void beRepaired (unsigned int amount);
	void log(void);

    protected:
    std::string _name;
    int _hitPoints;
    int _energyPoints;
    int _attackDamage;
};

#endif
