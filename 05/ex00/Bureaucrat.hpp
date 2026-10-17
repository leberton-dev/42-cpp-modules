#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <ostream>
#include <string>

class Bureaucrat {
    public:
    Bureaucrat (std::string name, int grade);
    Bureaucrat (const Bureaucrat& other);
    Bureaucrat& operator= (const Bureaucrat& other);
    ~Bureaucrat ();

    class GradeTooHighException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };
    class GradeTooLowException : public std::exception {
        public:
        virtual const char* what () const throw ();
    };

    const std::string& getName () const;
    int getGrade () const;
    void gradeIncrement ();
    void gradeDecrement ();

    private:
    const std::string _name;
    int _grade;
};

std::ostream& operator<< (std::ostream& out, const Bureaucrat& b);

#endif
