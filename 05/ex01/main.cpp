#include <iostream>

#include "Bureaucrat.hpp"
#include "Form.hpp"

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

static void tryCreateForm (const std::string& name, int sign, int exec) {
    try {
        Form f (name, sign, exec);
        std::cout << f << std::endl;
    } catch (std::exception& e) {
        std::cout << "Cannot create " << name << " (" << sign << ", " << exec
                  << "): " << e.what () << std::endl;
    }
}

int main (void) {
    title ("Bureaucrat: valid and invalid");
    tryCreate ("Boss", 1);
    tryCreate ("TooLow", 151);

    title ("Form: valid grades (unsigned at construction)");
    tryCreateForm ("Contract", 50, 25);
    tryCreateForm ("Limits", 1, 150);

    title ("Form: invalid grades");
    tryCreateForm ("SignZero", 0, 50);
    tryCreateForm ("Sign151", 151, 50);
    tryCreateForm ("ExecZero", 50, 0);
    tryCreateForm ("Exec151", 50, 151);

    Bureaucrat boss ("Boss", 1);
    Bureaucrat mid ("Mid", 50);
    Bureaucrat intern ("Intern", 150);

    title ("Mid (50) signs Contract (50): equal grade is enough");
    Form contract ("Contract", 50, 25);
    mid.signForm (contract);
    std::cout << contract << std::endl;

    title ("Intern (150) signs Secret (10): fail, stays unsigned");
    Form secret ("Secret", 10, 5);
    intern.signForm (secret);
    std::cout << secret << std::endl;

    title ("beSigned directly throws Form::GradeTooLowException");
    try {
        secret.beSigned (intern);
    } catch (Form::GradeTooLowException& e) {
        std::cout << "Caught: " << e.what () << std::endl;
    }

    title ("Boss signs Secret, then signs it again");
    boss.signForm (secret);
    boss.signForm (secret);
    std::cout << secret << std::endl;

    title ("Copy keeps signed, assignement copies only signed");
    Form copy (secret);
    Form other ("Other", 100, 100);
    other = secret;
    std::cout << copy << std::endl;
    std::cout << other << std::endl;
}
