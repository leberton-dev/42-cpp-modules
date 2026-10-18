#include "Form.hpp"

Form::Form (std::string name, const int grade_sign, const int grade_execute)
: _name (name), _signed (false), _grade_sign (grade_sign),
  _grade_execute (grade_execute) {
    if (grade_sign < 1 || grade_execute < 1)
        throw Form::GradeTooHighException ();
    if (grade_sign > 150 || grade_execute > 150)
        throw Form::GradeTooLowException ();
}

Form::Form (const Form& other)
: _name (other._name), _signed (other._signed), _grade_sign (other._grade_sign),
  _grade_execute (other._grade_execute) {
}

Form& Form::operator= (const Form& other) {
    if (this != &other) {
        _signed = other._signed;
    }
    return *this;
}

Form::~Form () {
}

const char* Form::GradeTooHighException::what () const throw () {
    return "Grade is too high";
}

const char* Form::GradeTooLowException::what () const throw () {
    return "Grade is too low";
}

const std::string& Form::getName () const {
    return _name;
}

bool Form::getSigned () const {
    return _signed;
}

int Form::getGradeSign () const {
    return _grade_sign;
}

int Form::getGradeExecute () const {
    return _grade_execute;
}

void Form::beSigned(const Bureaucrat& b) {
	if (b.getGrade() > _grade_sign)
		throw Form::GradeTooLowException();
	_signed = true;
}

std::ostream& operator<< (std::ostream& out, const Form& f) {
    out << f.getName () << ", signed " << f.getSigned () << ", grade sign "
        << f.getGradeSign () << ", grade execute " << f.getGradeExecute ();
    return out;
}
