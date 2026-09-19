#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#include <iostream>


static void test_subject_condition () {
    std::cout << "[ TESTING SUBJECT CONDITION ]" << std::endl;
    AAnimal* animals[4];

    for (int i = 0; i < 2; i++) {
        animals[i]     = new Dog ();
        animals[i + 2] = new Cat ();
    }

    for (int i = 0; i < 4; i++) {
        animals[i]->makeSound ();
    }

    for (int i = 0; i < 4; i++) {
        delete animals[i];
    }
    std::cout << std::endl;
}

static void test_brain_is_deep_copy () {
    std::cout << "[ TEST BRAIN IS DEEP COPY ]" << std::endl;

    const Dog* a = new Dog ();
    const Cat* c = new Cat ();
	a->getBrain()->ideas[0] = "This is what a dog could think";
	c->getBrain()->ideas[0] = "This is what a cat could think";

    const Dog* b = new Dog (*a);
    const Cat* d = new Cat (*c);

    std::cout << "	[ BEFORE DELETION ]" << std::endl;
    std::cout << "DogA brain tought 0: " << a->getBrain ()->ideas[0]  << std::endl;
    std::cout << "DogB brain tought 0: " << b->getBrain ()->ideas[0] << std::endl;
    std::cout << "CatC brain tought 0: " << c->getBrain ()->ideas[0]  << std::endl;
    std::cout << "CatD brain tought 0: " << d->getBrain ()->ideas[0] << std::endl;
    std::cout << std::endl;

    std::cout << "	[ AFTER DELETION ]" << std::endl;
    delete a;
	delete c;
    std::cout << "DogB brain tought 0: " << b->getBrain ()->ideas[0] << std::endl;
    std::cout << "CatD brain tought 0: " << d->getBrain ()->ideas[0] << std::endl;
    delete b;
    delete d;

    std::cout << std::endl;
}


// static void test_animal_not_instantiable() {
// 	AAnimal* a = new AAnimal();
//
// 	a->makeSound();
// }


int main (void) {
	test_subject_condition();
	test_brain_is_deep_copy();
	// test_animal_not_instantiable();
}
