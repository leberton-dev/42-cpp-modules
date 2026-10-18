#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <ostream>
#include <string>

class Form {
    public:
    Form (std::string name, const int grade_sign, const int grade_execute);
    Form (const Form& other);
    Form& operator= (const Form& other);
    ~Form ();
    class GradeTooHighException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };
    class GradeTooLowException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };

    const std::string& getName () const;
    bool getSigned () const;
    int getGradeSign () const;
    int getGradeExecute () const;

	void beSigned(const Bureaucrat& b);

    private:
    const std::string _name;
    bool _signed;
    const int _grade_sign;
    const int _grade_execute;
};

std::ostream& operator<< (std::ostream& out, const Form& f);

#endif
