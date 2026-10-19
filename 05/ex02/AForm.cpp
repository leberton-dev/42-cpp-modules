#include "AForm.hpp"

AForm::AForm (std::string name, const int grade_sign, const int grade_execute)
: _name (name), _signed (false), _grade_sign (grade_sign),
  _grade_execute (grade_execute) {
    if (grade_sign < 1 || grade_execute < 1)
        throw AForm::GradeTooHighException ();
    if (grade_sign > 150 || grade_execute > 150)
        throw AForm::GradeTooLowException ();
}

AForm::AForm (const AForm& other)
: _name (other._name), _signed (other._signed), _grade_sign (other._grade_sign),
  _grade_execute (other._grade_execute) {
}

AForm& AForm::operator= (const AForm& other) {
    if (this != &other) {
        _signed = other._signed;
    }
    return *this;
}

AForm::~AForm () {
}

const char* AForm::GradeTooHighException::what () const throw () {
    return "Grade is too high";
}

const char* AForm::GradeTooLowException::what () const throw () {
    return "Grade is too low";
}

const char* AForm::UnsignedFormException::what () const throw () {
    return "form is unsigned";
}

const std::string& AForm::getName () const {
    return _name;
}

bool AForm::getSigned () const {
    return _signed;
}

int AForm::getGradeSign () const {
    return _grade_sign;
}

int AForm::getGradeExecute () const {
    return _grade_execute;
}

void AForm::beSigned (const Bureaucrat& b) {
    if (b.getGrade () > _grade_sign)
        throw AForm::GradeTooLowException ();
    _signed = true;
}

std::ostream& operator<< (std::ostream& out, const AForm& f) {
    out << f.getName () << ", signed " << f.getSigned () << ", grade sign "
        << f.getGradeSign () << ", grade execute " << f.getGradeExecute ();
    return out;
}


void AForm::execute (Bureaucrat const& executor) const {
    if (!getSigned ())
        throw AForm::UnsignedFormException ();
    if (getGradeExecute () < executor.getGrade ())
        throw AForm::GradeTooLowException ();
}
