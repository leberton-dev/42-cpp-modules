#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Bureaucrat.hpp"
#include "Intern.hpp"

static void title (const std::string& s) {
    std::cout << "\n===== " << s << " =====" << std::endl;
}

int main (void) {
    std::srand (std::time (NULL));

    Bureaucrat boss ("Boss", 1);
    Intern randomIntern;
    AForm* form;

    title ("Subjects example");
    form = randomIntern.makeForm ("robotomy request", "Bender");
    std::cout << form->getName () << std::endl;
    delete form;
    form = randomIntern.makeForm ("shrubbery creation", "target");
    std::cout << form->getName () << std::endl;
    delete form;
    form = randomIntern.makeForm ("presidential pardon", "target");
    std::cout << form->getName () << std::endl;
    delete form;

    title ("Non-existent form");
    form = randomIntern.makeForm ("Robotomy Request", "nonexistent_target");
    delete form;

    title ("Form is signable and executable");
    form = randomIntern.makeForm ("robotomy request", "target");
    boss.signForm (*form);
    boss.executeForm (*form);
    delete form;
    form = randomIntern.makeForm ("shrubbery creation", "target");
    boss.signForm (*form);
    boss.executeForm (*form);
    delete form;
    form = randomIntern.makeForm ("presidential pardon", "target");
    boss.signForm (*form);
    boss.executeForm (*form);
    delete form;

    return 0;
}
