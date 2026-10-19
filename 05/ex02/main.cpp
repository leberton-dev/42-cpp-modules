#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <fstream>
#include <iostream>

static void ok (const std::string msg) {
    std::cout << "[" << "\033[0;32m" << "OK" << "\033[0m" << "] ";
    std::cout << msg << std::endl;
}

static void ko (const std::string msg) {
    std::cout << "[" << "\033[0;31m" << "KO" << "\033[0m" << "] ";
    std::cout << msg << std::endl;
}

#define CHECK(name, cond) ((cond) ? ok (name) : ko (name))

template <typename T>
static void form_grades (const std::string& prefix, int sign, int execute) {
    T f ("target");
    CHECK ((prefix + "_sign"), (f.getGradeSign () == sign));
    CHECK ((prefix + "_execute"), (f.getGradeExecute () == execute));
}

template <typename T>
static void form_name (const std::string& prefix, const std::string& correct_name) {
    T f ("target");
    CHECK (prefix + "_name", f.getName () == correct_name);
}

template <typename T>
static void form_not_signed_by_default (const std::string& prefix) {
    T f ("target");
    CHECK (prefix + "_form_not_signed_by_default", f.getSigned () == false);
}

template <typename T>
static void form_copy_keeps_signed (const std::string& prefix) {
    Bureaucrat b ("Bob", 1);
    T f ("target");
    f.beSigned (b);

    T copy (f);
    CHECK (prefix + "_copy_keeps_signed", copy.getSigned () == true);
}

template <typename T>
static void form_assign_copies_signed (const std::string& prefix) {
    Bureaucrat b ("Bob", 1);
    T f1 ("target");
    T f2 ("target");
    f1.beSigned (b);

    f2 = f1;
    CHECK (prefix + "_assign_copies_signed", (f2.getSigned () == true));
}

template <typename T>
static void form_delete_through_aform_pointer (const std::string& prefix) {
    AForm* f = new T ("target");
    try {
        delete f;
        ok (prefix + "_delete_through_aform_pointer");
    } catch (std::exception& e) {
        ko (prefix + "_delete_through_aform_pointer");
    }
}

// static void aform_not_instantiable() {
// 	AForm f("x", 1, 1);
// }

template <typename T>
static void execute_unsigned_throws (const std::string& prefix) {
    Bureaucrat b ("Bob", 1);
    T f ("target");

    try {
        f.execute (b);
        ko (prefix + "_execute_unsigned_throws: executed");
    } catch (AForm::UnsignedFormException& e) {
        ok (prefix + "_execute_unsigned_throws");
    } catch (std::exception& e) {
        ko (prefix + "_unsigned_throws: wrong exception: " + e.what ());
    }
}

template <typename T>
static void execute_grade_too_low_throws (const std::string& prefix) {
    Bureaucrat b ("Bob", 1);
    Bureaucrat low_b ("LowBob", 150);
    T f ("target");
    f.beSigned (b);

    try {
        f.execute (low_b);
        ko (prefix + "_execute_grade_too_low_throws: executed");
    } catch (AForm::GradeTooLowException& e) {
        ok (prefix + "_execute_grade_too_low_throws");
    } catch (std::exception& e) {
        ko (prefix + "_unsigned_throws: wrong exception: " + e.what ());
    }
}

template <typename T>
static void execute_grade_equal_ok (const std::string& prefix, int grade) {
    Bureaucrat b ("Bob", grade);
    T f ("target");
    f.beSigned (b);

    try {
        f.execute (b);
        ok (prefix + "_execute_grade_equal_ok");
    } catch (std::exception& e) {
        ko (prefix + "_execute_grade_equal_ok: got exception: " + e.what ());
    }
}

template <typename T>
static void execute_grade_one_below_throws (const std::string& prefix, int grade) {
    Bureaucrat b ("Bob", grade + 1);
    T f ("target");
    f.beSigned (b);

    try {
        f.execute (b);
        ko (prefix + "_execute_grade_one_below_throws: executed");
    } catch (AForm::GradeTooLowException& e) {
        ok (prefix + "_execute_grade_one_below_throws");
    } catch (std::exception& e) {
        ko (prefix + "_execute_grade_one_below_throws: wrong exception: " + e.what ());
    }
}

static void shrubbery_creates_file () {
    Bureaucrat b ("Bob", 1);
    ShrubberyCreationForm f ("target");
    f.beSigned (b);
    f.execute (b);

    std::ifstream ifs ("target_shrubbery");
    CHECK ("shrubbery_creates_file", ifs.good ());
}

static void shrubbery_file_not_empty () {
    Bureaucrat b ("Bob", 1);
    ShrubberyCreationForm f ("target");
    f.beSigned (b);
    f.execute (b);

    std::ifstream ifs ("target_shrubbery");
    CHECK ("shrubbery_file_not_empty",
    (ifs.is_open () && ifs.peek () != std::ifstream::traits_type::eof ()));
}

static void shrubbery_open_failure_throws () {
    Bureaucrat b ("Bob", 1);
    ShrubberyCreationForm f ("this_does_not_exist/hahahaha");
    f.beSigned (b);
    try {
        f.execute (b);
        ko ("shrubbery_open_failure_throws: executed");
    } catch (ShrubberyCreationForm::CouldNotOpenFileException& e) {
        ok ("shrubbery_open_failure_throws");
    } catch (std::exception& e) {
        const std::string prefix = "shrubbery_open_failure_throws";
        ko (prefix + ": wrong exception: " + e.what ());
    }
}

int main (void) {
    // Forms: Construction and copy
    form_grades<ShrubberyCreationForm> ("shrubbery", 145, 137);
    form_grades<RobotomyRequestForm> ("robotomy", 72, 45);
    form_grades<PresidentialPardonForm> ("presidential", 25, 5);

    form_name<ShrubberyCreationForm> ("shrubbery", "ShrubberyCreationForm");
    form_name<RobotomyRequestForm> ("robotomy", "RobotomyRequestForm");
    form_name<PresidentialPardonForm> ("presidential", "PresidentialPardonForm");

    form_not_signed_by_default<ShrubberyCreationForm> ("shrubbery");
    form_not_signed_by_default<RobotomyRequestForm> ("robotomy");
    form_not_signed_by_default<PresidentialPardonForm> ("presidential");

    form_copy_keeps_signed<ShrubberyCreationForm> ("shrubbery");
    form_copy_keeps_signed<RobotomyRequestForm> ("robotomy");
    form_copy_keeps_signed<PresidentialPardonForm> ("presidential");

    form_assign_copies_signed<ShrubberyCreationForm> ("shrubbery");
    form_assign_copies_signed<RobotomyRequestForm> ("robotomy");
    form_assign_copies_signed<PresidentialPardonForm> ("presidential");

    form_delete_through_aform_pointer<ShrubberyCreationForm> ("shrubbery");
    form_delete_through_aform_pointer<RobotomyRequestForm> ("robotomy");
    form_delete_through_aform_pointer<PresidentialPardonForm> ("presidential");

    // aform_not_instantiable();

    // Execute: conditions
    execute_unsigned_throws<ShrubberyCreationForm> ("shrubbery");
    execute_unsigned_throws<RobotomyRequestForm> ("robotomy");
    execute_unsigned_throws<PresidentialPardonForm> ("presidential");

    execute_grade_too_low_throws<ShrubberyCreationForm> ("shrubbery");
    execute_grade_too_low_throws<RobotomyRequestForm> ("robotomy");
    execute_grade_too_low_throws<PresidentialPardonForm> ("presidential");

    execute_grade_equal_ok<ShrubberyCreationForm> ("shrubbery", 137);
    execute_grade_equal_ok<RobotomyRequestForm> ("robotomy", 45);
    execute_grade_equal_ok<PresidentialPardonForm> ("presidential", 5);

    execute_grade_one_below_throws<ShrubberyCreationForm> ("shrubbery", 137);
    execute_grade_one_below_throws<RobotomyRequestForm> ("robotomy", 45);
    execute_grade_one_below_throws<PresidentialPardonForm> ("presidential", 5);

    // Shrubbery
    shrubbery_creates_file ();
    shrubbery_file_not_empty ();
    shrubbery_open_failure_throws ();
}
