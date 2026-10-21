#include <cstdlib>
#include <iostream>

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm (const std::string& target_form)
: AForm ("RobotomyRequestForm", 72, 45), _target_form (target_form) {
}

RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm& other)
: AForm (other), _target_form (other._target_form) {
}

RobotomyRequestForm& RobotomyRequestForm::operator= (const RobotomyRequestForm& other) {
    if (this != &other)
        AForm::operator= (other);
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm () {
}

void RobotomyRequestForm::execute (Bureaucrat const& executor) const {
    AForm::execute (executor);
    std::cout << "SOME DRILLING NOISES..." << std::endl;

    if (std::rand () % 2)
        std::cout << _target_form << " has been robotomized successfully!" << std::endl;
    else
        std::cout << "Robotomy failed." << std::endl;
}
