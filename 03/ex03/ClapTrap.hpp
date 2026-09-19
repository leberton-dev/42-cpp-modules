#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

#define BLUE "\033[1;34m"
#define RESET "\033[0m"

#define CLAPTRAP_HP 10
#define CLAPTRAP_EP 10
#define CLAPTRAP_AD 0

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
