#include <iostream>

#include "PresidentialPardonForm.hpp"


PresidentialPardonForm::PresidentialPardonForm (const std::string& target_form)
: AForm ("PresidentialPardonForm", 25, 5), _target_form (target_form) {
}

PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm& other)
: AForm (other), _target_form (other._target_form) {
}

PresidentialPardonForm& PresidentialPardonForm::operator= (
const PresidentialPardonForm& other) {
    if (this != &other)
        AForm::operator= (other);
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm () {
}

void PresidentialPardonForm::execute (Bureaucrat const& executor) const {
    AForm::execute (executor);
    std::cout << _target_form << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
