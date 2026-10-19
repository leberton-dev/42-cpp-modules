#ifndef SHUBERRY_CREATION_FORM_HPP
#define SHUBERRY_CREATION_FORM_HPP

#include <string>

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class ShrubberyCreationForm : public AForm {
    public:
    ShrubberyCreationForm (const std::string& target_form);
    ShrubberyCreationForm (const ShrubberyCreationForm& s);
    ShrubberyCreationForm operator= (const ShrubberyCreationForm& s);
    ~ShrubberyCreationForm ();

    void execute (Bureaucrat const& executor) const;

    class CouldNotOpenFileException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };

    private:
    const std::string _target_form;
};

#endif
