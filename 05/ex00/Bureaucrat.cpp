#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat (std::string name, int grade) : _name (name) {
    if (grade > 150)
        throw GradeTooLowException ();
    if (grade < 1)
        throw GradeTooHighException ();
    _grade = grade;
}

Bureaucrat::Bureaucrat (const Bureaucrat& other)
: _name (other._name), _grade (other._grade) {
}

Bureaucrat& Bureaucrat::operator= (const Bureaucrat& other) {
    if (this != &other)
        _grade = other._grade;
    return *this;
}

Bureaucrat::~Bureaucrat () {
}

const char* Bureaucrat::GradeTooHighException::what () const throw () {
    return "Grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what () const throw () {
    return "Grade is too low";
}

const std::string& Bureaucrat::getName () const {
    return _name;
}

int Bureaucrat::getGrade () const {
    return _grade;
}

void Bureaucrat::gradeIncrement () {
    if (_grade == 1)
        throw GradeTooHighException ();
    _grade--;
}

void Bureaucrat::gradeDecrement () {
    if (_grade == 150)
        throw GradeTooLowException ();
    _grade++;
}

std::ostream& operator<< (std::ostream& out, const Bureaucrat& b) {
    out << b.getName () << ", bureaucrat grade " << b.getGrade () << ".";
    return out;
}
