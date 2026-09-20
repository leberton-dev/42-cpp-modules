#include "ScavTrap.hpp"

#include <iostream>


static void instanciatesWithRequiredParams (ScavTrap& bob) {
    std::cout << "[ INSTANCIATES WITH REQUIRED PARAMS ]" << std::endl;
    bob.log ();
    std::cout << std::endl;
}

static void attacksWithEnergyAndHitPoints (ScavTrap& bob) {
    std::cout << "[ ATTACKS WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void attacksWithoutEnergy (ScavTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT ENERGY ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void attackWithoutHitPoints (ScavTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void repairWithEnergyAndHitPoints (ScavTrap& bob) {
    std::cout << "[ REPAIR WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void repairWithoutEnergy (ScavTrap& bob) {
    std::cout << "[ REPAIR WITHOUT ENERGY ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void healWithoutHitPoints (ScavTrap& bob) {
    std::cout << "[ REPAIR WITHOUT HIT POINTS ]" << std::endl;
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void hitPointsAffectedCorrectly (ScavTrap& bob) {
    std::cout << "[ HIT POINTS AFFECTED CORRECLY ]" << std::endl;
    bob.takeDamage (100);
    std::cout << std::endl;
}

static void hitPointsDoNotGoBelowZero (ScavTrap& bob) {
    std::cout << "[ HIT POINTS DO NOT GO BELOW ZERO ]" << std::endl;
    bob.takeDamage (1);
    std::cout << std::endl;
}

static void attackRemovesEnergy (ScavTrap& bob) {
    std::cout << "[ ATTACK REMOVES ENERGY ]" << std::endl;
    for (int i = 0; i < 50; i++)
        bob.attack ("John");
    std::cout << std::endl;
}

static void activateGuardGateMode(ScavTrap& bob) {
    std::cout << "[ ACTIVATE GUARD GATE MODE ]" << std::endl;
	bob.guardGate();
    std::cout << std::endl;

}

static void defaultConstructorEstablished() {
    std::cout << "[ DEFAULT CONSTRUCTOR ESTABLISHED ]" << std::endl;
	ScavTrap bob = ScavTrap();
    std::cout << std::endl;
}

static ScavTrap parameterizedConstructorEstablished(std::string name) {
    std::cout << "[ PARAMETERIZED CONSTRUCTOR ESTABLISHED ]" << std::endl;
	ScavTrap st = ScavTrap(name);
    std::cout << std::endl;

	return st;
}

static void copyConstructorEstablished(ScavTrap& bob) {
    std::cout << "[ COPY CONSTRUCTOR ESTABLISHED ]" << std::endl;
	ScavTrap st = ScavTrap(bob);
    std::cout << std::endl;
}

static void copyAssignmentConstructorEstablished(ScavTrap* old, std::string name)
{
    std::cout << "[ COPY ASSIGNMENT CONSTRUCTOR ESTABLISHED ]" << std::endl;
	*old = ScavTrap(name);
    std::cout << std::endl;
}

static void pointerScavTrapDeletes() {
	std::cout << "[ POINTER SCAV TRAP DELETES ]" << std::endl;
	ScavTrap* bob = new ScavTrap();
	delete bob;
	std::cout << std::endl;
}


int main (void) {
	defaultConstructorEstablished();
	ScavTrap bob = parameterizedConstructorEstablished("Constructor Bob");
	copyConstructorEstablished(bob);
	copyAssignmentConstructorEstablished(&bob, "Bob");

    instanciatesWithRequiredParams (bob);
    attacksWithEnergyAndHitPoints (bob);
    repairWithEnergyAndHitPoints (bob);

    bob = ScavTrap ("no hp Bob");
    std::cout << std::endl;
    hitPointsAffectedCorrectly (bob);
    attackWithoutHitPoints (bob);
    healWithoutHitPoints (bob);
    hitPointsDoNotGoBelowZero (bob);

    bob = ScavTrap ("no energy Bob");
    std::cout << std::endl;
    attackRemovesEnergy (bob);
    attacksWithoutEnergy (bob);
    repairWithoutEnergy (bob);

	activateGuardGateMode(bob);
	pointerScavTrapDeletes();
}
