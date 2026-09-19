#include "DiamondTrap.hpp"

#include <iostream>


static void instanciatesWithRequiredParams (DiamondTrap& bob) {
    std::cout << "[ INSTANCIATES WITH REQUIRED PARAMS ]" << std::endl;
    bob.log ();
    std::cout << std::endl;
}

static void attacksWithEnergyAndHitPoints (DiamondTrap& bob) {
    std::cout << "[ ATTACKS WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void attacksWithoutEnergy (DiamondTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT ENERGY ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void attackWithoutHitPoints (DiamondTrap& bob) {
    std::cout << "[ ATTACKS WITHOUT HIT POINTS ]" << std::endl;
    bob.attack ("John");
    std::cout << std::endl;
}

static void repairWithEnergyAndHitPoints (DiamondTrap& bob) {
    std::cout << "[ REPAIR WITH ENERGY AND HIT POINTS ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void repairWithoutEnergy (DiamondTrap& bob) {
    std::cout << "[ REPAIR WITHOUT ENERGY ]" << std::endl;
    bob.takeDamage (1);
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void healWithoutHitPoints (DiamondTrap& bob) {
    std::cout << "[ REPAIR WITHOUT HIT POINTS ]" << std::endl;
    bob.beRepaired (1);
    std::cout << std::endl;
}

static void hitPointsAffectedCorrectly (DiamondTrap& bob) {
    std::cout << "[ HIT POINTS AFFECTED CORRECLY ]" << std::endl;
    bob.takeDamage (100);
    std::cout << std::endl;
}

static void hitPointsDoNotGoBelowZero (DiamondTrap& bob) {
    std::cout << "[ HIT POINTS DO NOT GO BELOW ZERO ]" << std::endl;
    bob.takeDamage (1);
    std::cout << std::endl;
}

static void attackRemovesEnergy (DiamondTrap& bob) {
    std::cout << "[ ATTACK REMOVES ENERGY ]" << std::endl;
    for (int i = 0; i < 50; i++)
        bob.attack ("John");
    std::cout << std::endl;
}

static void activateHighFivesGuys (DiamondTrap& bob) {
    std::cout << "[ ACTIVATE HIGH FIVES GUYS ]" << std::endl;
    bob.highFivesGuys ();
    std::cout << std::endl;
}

static void activateGuardGateMode (ScavTrap& bob) {
    std::cout << "[ ACTIVATE GUARD GATE MODE ]" << std::endl;
    bob.guardGate ();
    std::cout << std::endl;
}

static void defaultConstructorEstablished () {
    std::cout << "[ DEFAULT CONSTRUCTOR ESTABLISHED ]" << std::endl;
    DiamondTrap bob = DiamondTrap ();
    std::cout << std::endl;
}

static DiamondTrap parameterizedConstructorEstablished (std::string name) {
    std::cout << "[ PARAMETERIZED CONSTRUCTOR ESTABLISHED ]" << std::endl;
    DiamondTrap st = DiamondTrap (name);
    std::cout << std::endl;

    return st;
}

static void copyConstructorEstablished (DiamondTrap& bob) {
    std::cout << "[ COPY CONSTRUCTOR ESTABLISHED ]" << std::endl;
    DiamondTrap st = DiamondTrap (bob);
    std::cout << std::endl;
}

static void copyAssignmentConstructorEstablished (DiamondTrap* old, std::string name) {
    std::cout << "[ COPY ASSIGNMENT CONSTRUCTOR ESTABLISHED ]" << std::endl;
    *old = DiamondTrap (name);
    std::cout << std::endl;
}

static void whoAmIMethod (DiamondTrap& bob) {
    std::cout << "[ WHOAMI METHOD ]" << std::endl;
    bob.whoAmI ();
    std::cout << std::endl;
}


int main (void) {
    defaultConstructorEstablished ();
    DiamondTrap bob = parameterizedConstructorEstablished ("Constructor Bob");
    copyConstructorEstablished (bob);
    copyAssignmentConstructorEstablished (&bob, "Bob");

    instanciatesWithRequiredParams (bob);
    attacksWithEnergyAndHitPoints (bob);
    repairWithEnergyAndHitPoints (bob);

    bob = DiamondTrap ("no hp Bob");
    std::cout << std::endl;
    hitPointsAffectedCorrectly (bob);
    attackWithoutHitPoints (bob);
    healWithoutHitPoints (bob);
    hitPointsDoNotGoBelowZero (bob);

    bob = DiamondTrap ("no energy Bob");
    std::cout << std::endl;
    attackRemovesEnergy (bob);
    attacksWithoutEnergy (bob);
    repairWithoutEnergy (bob);

    activateHighFivesGuys (bob);
    activateGuardGateMode (bob);
    whoAmIMethod (bob);
}
