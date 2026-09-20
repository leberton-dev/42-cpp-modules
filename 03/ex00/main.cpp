#include "ClapTrap.hpp"

#include <iostream>


void instanciatesWithRequiredParams (ClapTrap& bob) {
    std::cout << "[ INSTANCIATES WITH REQUIRED PARAMS ]" << std::endl;
    bob.log ();
    std::cout << std::endl;
}

void attacksWithEnergyAndHitPoints (ClapTrap& bob) {
    std::cout << "[ ATTACKS WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

void attacksWithoutEnergy (ClapTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT ENERGY ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

void attackWithoutHitPoints (ClapTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

void repairWithEnergyAndHitPoints (ClapTrap& bob) {
    std::cout << "[ REPAIR WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

void repairWithoutEnergy (ClapTrap& bob) {
    std::cout << "[ REPAIR WITHOUT ENERGY ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

void healWithoutHitPoints (ClapTrap& bob) {
    std::cout << "[ REPAIR WITHOUT HIT POINTS ]" << std::endl;
    bob.beRepaired (1);
    std::cout << std::endl;
}

void hitPointsAffectedCorrectly (ClapTrap& bob) {
    std::cout << "[ HIT POINTS AFFECTED CORRECLY ]" << std::endl;
    bob.takeDamage (10);
    std::cout << std::endl;
}

void hitPointsDoNotGoBelowZero (ClapTrap& bob) {
    std::cout << "[ HIT POINTS DO NOT GO BELOW ZERO ]" << std::endl;
    bob.takeDamage (1);
    std::cout << std::endl;
}

void attackRemovesEnergy (ClapTrap& bob) {
    std::cout << "[ ATTACK REMOVES ENERGY ]" << std::endl;
    for (int i = 0; i < 10; i++)
        bob.attack ("John");
    std::cout << std::endl;
}

static void pointerClapTrapDeletes() {
	std::cout << "[ POINTER CLAP TRAP DELETES ]" << std::endl;
	ClapTrap* bob = new ClapTrap();
	delete bob;
	std::cout << std::endl;
}

int main (void) {
    ClapTrap bob = ClapTrap ("Bob");

    instanciatesWithRequiredParams (bob);
    attacksWithEnergyAndHitPoints (bob);
    repairWithEnergyAndHitPoints (bob);


    bob = ClapTrap ("no hp Bob");
    std::cout << std::endl;
    hitPointsAffectedCorrectly (bob);
    attackWithoutHitPoints (bob);
    healWithoutHitPoints (bob);
    hitPointsDoNotGoBelowZero (bob);

    bob = ClapTrap ("no energy Bob");
    std::cout << std::endl;
    attackRemovesEnergy (bob);
    attacksWithoutEnergy (bob);
    repairWithoutEnergy (bob);

	pointerClapTrapDeletes();
}
