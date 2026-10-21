#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

static void title (const std::string& s) {
    std::cout << "\n===== " << s << " =====" << std::endl;
}

int main (void) {
    std::srand (std::time (NULL));
    Bureaucrat boss ("Boss", 1);
    Bureaucrat mid ("Mid", 140);
    Bureaucrat intern ("Intern", 150);

    title ("Boss signs and executes every form");
    ShrubberyCreationForm s ("home");
    RobotomyRequestForm r ("robotomo");
    PresidentialPardonForm p ("mcdonald");
    AForm* forms[] = { &s, &r, &p };
    for (int i = 0; i < 3; i++) {
        std::cout << *forms[i] << std::endl;
        boss.signForm (*forms[i]);
        boss.executeForm (*forms[i]);
    }

    title ("Execute an unsigned form");
    PresidentialPardonForm unsigned_p ("harvey");
    boss.executeForm (unsigned_p);

    title ("Mid (140) can sign Shrubbery (145) but not execute it (137)");
    ShrubberyCreationForm workshop ("workshop");
    mid.signForm (workshop);
    mid.executeForm (workshop);

    title ("Intern (150) cannot sign Presidential (25)");
    intern.signForm (unsigned_p);

    title ("Robotomy x6: about half should succeed");
    for (int i = 0; i < 6; i++)
        boss.executeForm (r);
}
