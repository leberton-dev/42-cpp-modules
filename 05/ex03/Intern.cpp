#include <iostream>

#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern () {
}

Intern::Intern (const Intern& i) {
    (void)i;
}

Intern& Intern::operator= (const Intern& i) {
    (void)i;
    return *this;
}

Intern::~Intern () {
}

static AForm* createShrubbery (const std::string& target) {
    return new ShrubberyCreationForm (target);
}

static AForm* createRobotomy (const std::string& target) {
    return new RobotomyRequestForm (target);
}

static AForm* createPresidential (const std::string& target) {
    return new PresidentialPardonForm (target);
}

AForm* Intern::makeForm (const std::string& name, const std::string& target) {
	const std::string names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm* (*creators[3])(const std::string& target) = {
		&createShrubbery,
		&createRobotomy,
		&createPresidential,
	};

	for (int i = 0; i < 3; i++) {
		if (names[i] == name) {
			std::cout << "Intern creates " << name << std::endl;
			return creators[i](target);
		}
	}
	std::cerr << "Intern cannot find form \"" << name << "\"" << std::endl;
	return NULL;
}
