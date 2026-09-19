#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>


int main (void) {

    const Animal* meta = new Animal ();
    const Animal* j    = new Dog ();
    const Animal* i    = new Cat ();

    std::cout << meta->getType () << " " << std::endl;
    std::cout << j->getType () << " " << std::endl;
    std::cout << i->getType () << " " << std::endl;
    i->makeSound (); // will output the cat sound!
    j->makeSound ();
    meta->makeSound ();

	delete meta;
	delete j;
	delete i;

	const WrongAnimal* wmeta = new WrongAnimal();
	const WrongAnimal* wcat = new WrongCat();

    std::cout << wmeta->getType () << " " << std::endl;
    std::cout << wcat->getType () << " " << std::endl;
    wcat->makeSound (); // will output the wrong cat sound!
    wmeta->makeSound ();

	delete wmeta;
	delete wcat;
}
