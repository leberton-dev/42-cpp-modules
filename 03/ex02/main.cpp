#include "FragTrap.hpp"

#include <iostream>


static void instanciatesWithRequiredParams (FragTrap& bob) {
    std::cout << "[ INSTANCIATES WITH REQUIRED PARAMS ]" << std::endl;
    bob.log ();
    std::cout << std::endl;
}

static void attacksWithEnergyAndHitPoints (FragTrap& bob) {
    std::cout << "[ ATTACKS WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void attacksWithoutEnergy (FragTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT ENERGY ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void attackWithoutHitPoints (FragTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void repairWithEnergyAndHitPoints (FragTrap& bob) {
    std::cout << "[ REPAIR WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void repairWithoutEnergy (FragTrap& bob) {
    std::cout << "[ REPAIR WITHOUT ENERGY ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void healWithoutHitPoints (FragTrap& bob) {
    std::cout << "[ REPAIR WITHOUT HIT POINTS ]" << std::endl;
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void hitPointsAffectedCorrectly (FragTrap& bob) {
    std::cout << "[ HIT POINTS AFFECTED CORRECLY ]" << std::endl;
    bob.takeDamage (100);
    std::cout << std::endl;
}

static void hitPointsDoNotGoBelowZero (FragTrap& bob) {
    std::cout << "[ HIT POINTS DO NOT GO BELOW ZERO ]" << std::endl;
    bob.takeDamage (1);
    std::cout << std::endl;
}

static void attackRemovesEnergy (FragTrap& bob) {
    std::cout << "[ ATTACK REMOVES ENERGY ]" << std::endl;
    for (int i = 0; i < 100; i++)
        bob.attack ("John");
    std::cout << std::endl;
}

static void activateHighFivesGuys(FragTrap& bob) {
    std::cout << "[ ACTIVATE HIGH FIVES GUYS ]" << std::endl;
	bob.highFivesGuys();
    std::cout << std::endl;

}

static void defaultConstructorEstablished() {
    std::cout << "[ DEFAULT CONSTRUCTOR ESTABLISHED ]" << std::endl;
	FragTrap bob = FragTrap();
    std::cout << std::endl;
}

static FragTrap parameterizedConstructorEstablished(std::string name) {
    std::cout << "[ PARAMETERIZED CONSTRUCTOR ESTABLISHED ]" << std::endl;
	FragTrap st = FragTrap(name);
    std::cout << std::endl;

	return st;
}

static void copyConstructorEstablished(FragTrap& bob) {
    std::cout << "[ COPY CONSTRUCTOR ESTABLISHED ]" << std::endl;
	FragTrap st = FragTrap(bob);
    std::cout << std::endl;
}

static void copyAssignmentConstructorEstablished(FragTrap* old, std::string name)
{
    std::cout << "[ COPY ASSIGNMENT CONSTRUCTOR ESTABLISHED ]" << std::endl;
	*old = FragTrap(name);
    std::cout << std::endl;
}


int main (void) {
	defaultConstructorEstablished();
	FragTrap bob = parameterizedConstructorEstablished("Constructor Bob");
	copyConstructorEstablished(bob);
	copyAssignmentConstructorEstablished(&bob, "Bob");

    instanciatesWithRequiredParams (bob);
    attacksWithEnergyAndHitPoints (bob);
    repairWithEnergyAndHitPoints (bob);

    bob = FragTrap ("no hp Bob");
    std::cout << std::endl;
    hitPointsAffectedCorrectly (bob);
    attackWithoutHitPoints (bob);
    healWithoutHitPoints (bob);
    hitPointsDoNotGoBelowZero (bob);

    bob = FragTrap ("no energy Bob");
    std::cout << std::endl;
    attackRemovesEnergy (bob);
    attacksWithoutEnergy (bob);
    repairWithoutEnergy (bob);

	activateHighFivesGuys(bob);
}
