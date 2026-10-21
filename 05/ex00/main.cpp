#include <iostream>

#include "Bureaucrat.hpp"

static void title (const std::string& s) {
    std::cout << std::endl << "===== " << s << " =====" << std::endl;
}

static void tryCreate (const std::string& name, int grade) {
    try {
        Bureaucrat b (name, grade);
        std::cout << b << std::endl;
    } catch (std::exception& e) {
        std::cout << "Cannot create " << name << " (" << grade
                  << "):" << e.what () << std::endl;
    }
}

int main (void) {
    title ("Valid grades: 1, 150, 75");
    tryCreate ("Boss", 1);
    tryCreate ("Intern", 150);
    tryCreate ("Mid", 75);

    title ("Invalid grades: 0, 151, -42");
    tryCreate ("Zero", 0);
    tryCreate ("TooLow", 151);
    tryCreate ("Negative", -42);

    title ("Bob (3): increment -> 2, then decrement twice -> 4");
    Bureaucrat bob ("Bob", 3);
    bob.gradeIncrement ();
    std::cout << bob << std::endl;
    bob.gradeDecrement ();
    bob.gradeDecrement ();
    std::cout << bob << std::endl;

    title ("Boss (1) increment: throws, grade unchanged");
    Bureaucrat boss ("Boss", 1);
    try {
        boss.gradeIncrement ();
    } catch (std::exception& e) {
        std::cout << "Caught: " << e.what () << std::endl;
    }
    std::cout << boss << std::endl;

    title ("Intern (150) decrement: throws, grade unchanged");
    Bureaucrat intern ("Intern", 150);
    try {
        intern.gradeDecrement ();
    } catch (std::exception& e) {
        std::cout << "Caught: " << e.what () << std::endl;
    }
    std::cout << intern << std::endl;

    title ("Copy of Bob, then Alice = Boss (keeps her name)");
    Bureaucrat copy (bob);
    Bureaucrat alice ("Alice", 100);
    alice = boss;
    std::cout << copy << std::endl;
    std::cout << alice << std::endl;
}
