#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"

#include <fstream>
#include <iostream>


ShrubberyCreationForm::ShrubberyCreationForm (const std::string& target_form)
: AForm ("ShrubberyCreationForm", 145, 137), _target_form (target_form) {
}

ShrubberyCreationForm::ShrubberyCreationForm (const ShrubberyCreationForm& other)
: AForm (other), _target_form (other._target_form) {
}

ShrubberyCreationForm ShrubberyCreationForm::operator= (const ShrubberyCreationForm& other) {
    if (this != &other) {
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm () {
}

void ShrubberyCreationForm::execute (Bureaucrat const& executor) const {
    if (!getSigned ())
        throw AForm::UnsignedFormException ();
    if (getGradeExecute () < executor.getGrade ())
        throw AForm::GradeTooLowException ();

    std::ofstream file ((getName () + "_shrubbery").c_str ());
    if (!file.is_open ()) {
        std::cerr << "Couldn't open file" << std::endl;
        return;
    }

    file << "                                  # #### ####" << std::endl;
    file << "                                ### \\/#|### |/####" << std::endl;
    file << "                               ##\\/#/ \\||/##/_/##/_#" << std::endl;
    file << "                             ###  \\d/###|/ \\/ # ###" << std::endl;
    file << "                           ##_\\_#\\_\\## | #/###_/_####" << std::endl;
    file << "                          ## #### # \\ #| /  #### ##/##" << std::endl;
    file << "                           __#_--###`  |{,###---###-~" << std::endl;
    file << "                                     \\ }{" << std::endl;
    file << "                                      }}{" << std::endl;
    file << "                                      }}{" << std::endl;
    file << "                                 ejm  {{}" << std::endl;
    file << "                                , -=-~{ .-^- _" << std::endl;
    file << "                                      `}" << std::endl;
    file << "                                       {" << std::endl;
}
