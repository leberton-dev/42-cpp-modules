#ifndef PRESIDENTIAL_PARDON_FORM_HPP
#define PRESIDENTIAL_PARDON_FORM_HPP

#include "AForm.hpp"
#include <string>

class PresidentialPardonForm : public AForm {
    public:
    PresidentialPardonForm (const std::string& target_form);
    PresidentialPardonForm (const PresidentialPardonForm& other);
    PresidentialPardonForm operator= (const PresidentialPardonForm& other);
    ~PresidentialPardonForm ();

    void execute (Bureaucrat const& executor) const;

    private:
    const std::string _target_form;
};

#endif
