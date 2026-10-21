#ifndef ROBOTOMY_REQUEST_FORM_HPP
#define ROBOTOMY_REQUEST_FORM_HPP

#include "AForm.hpp"
#include <string>

class RobotomyRequestForm : public AForm {
    public:
    RobotomyRequestForm (const std::string& target_form);
    RobotomyRequestForm (const RobotomyRequestForm& other);
    RobotomyRequestForm& operator= (const RobotomyRequestForm& other);
    ~RobotomyRequestForm ();

    void execute (Bureaucrat const& executor) const;

    private:
    const std::string _target_form;
};

#endif
