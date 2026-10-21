#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <ostream>
#include <string>

class AForm {
    public:
    AForm (std::string name, const int grade_sign, const int grade_execute);
    AForm (const AForm& other);
    AForm& operator= (const AForm& other);
    virtual ~AForm () = 0;
    class GradeTooHighException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };
    class GradeTooLowException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };
    class UnsignedFormException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };

    const std::string& getName () const;
    bool getSigned () const;
    int getGradeSign () const;
    int getGradeExecute () const;

    void beSigned (const Bureaucrat& b);

    virtual void execute (Bureaucrat const& executor) const = 0;

    private:
    const std::string _name;
    bool _signed;
    const int _grade_sign;
    const int _grade_execute;
};

std::ostream& operator<< (std::ostream& out, const AForm& f);

#endif
