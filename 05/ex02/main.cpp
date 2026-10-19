#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <fstream>
#include <iostream>

static const Bureaucrat boss ("Boss", 1);
static const Bureaucrat new_guy ("NewGuy", 150);

static void ok (const std::string msg) {
    std::cout << "[" << "\033[0;32m" << "OK" << "\033[0m" << "] ";
    std::cout << msg << std::endl;
}

static void ko (const std::string msg) {
    std::cout << "[" << "\033[0;31m" << "KO" << "\033[0m" << "] ";
    std::cout << msg << std::endl;
}

static std::string upper (std::string s) {
    for (size_t i = 0; i < s.size (); ++i)
        s[i] = std::toupper (static_cast<unsigned char> (s[i]));
    return s;
}

#define CHECK(name, cond) ((cond) ? ok (name) : ko (name))
#define EXPECT_THROW(name, X, E)                                         \
    do {                                                                 \
        try {                                                            \
            X;                                                           \
            ko (std::string (name) + ": executed");                      \
        } catch (E&) {                                                   \
            ok (std::string (name));                                     \
        } catch (std::exception & e) {                                   \
            ko (std::string (name) + ": wrong exception: " + e.what ()); \
        }                                                                \
    } while (0)
#define EXPECT_NO_THROW(name, X)                                          \
    do {                                                                  \
        try {                                                             \
            X;                                                            \
            ok (std::string (name));                                      \
        } catch (std::exception & e) {                                    \
            ko (std::string (name) + ": caught exception: " + e.what ()); \
        }                                                                 \
    } while (0)

template <typename T> struct Info;

#define INFO(T, p, s, e)                     \
    template <> struct Info<T> {             \
        static std::string prefix () {       \
            return p;                        \
        }                                    \
        static std::string correct_name () { \
            return #T;                       \
        }                                    \
        static const int sign    = s;        \
        static const int execute = e;        \
    }

INFO (ShrubberyCreationForm, "shrubbery", 145, 137);
INFO (RobotomyRequestForm, "robotomy", 72, 45);
INFO (PresidentialPardonForm, "presidential", 25, 5);

#define NAME (Info<T>::prefix () + "_" + __FUNCTION__)
#define TITLE (upper (__FUNCTION__) + "_" + upper (Info<T>::prefix ()))


template <typename T> static void form_grades () {
    T f ("target");
    CHECK (NAME + "_sign", f.getGradeSign () == Info<T>::sign);
    CHECK (NAME + "_execute", f.getGradeExecute () == Info<T>::execute);
}

template <typename T> static void form_name () {
    T f ("target");
    CHECK (NAME, f.getName () == Info<T>::correct_name ());
}

template <typename T> static void form_not_signed_by_default () {
    T f ("target");
    CHECK (NAME, f.getSigned () == false);
}

template <typename T> static void form_copy_keeps_signed () {
    T f ("target");
    f.beSigned (boss);
    T copy (f);
    CHECK (NAME, copy.getSigned () == true);
}

template <typename T> static void form_assign_copies_signed () {
    T f1 ("target");
    T f2 ("target");
    f1.beSigned (boss);
    f2 = f1;
    CHECK (NAME, (f2.getSigned () == true));
}

template <typename T> static void form_delete_through_aform_pointer () {
    AForm* f = new T ("target");
    EXPECT_NO_THROW (NAME, delete f);
}

template <typename T> static void execute_unsigned_throws () {
    T f ("target");
    EXPECT_THROW (NAME, f.execute (boss), AForm::UnsignedFormException);
}

template <typename T> static void execute_grade_too_low_throws () {
    T f ("target");
    f.beSigned (boss);
    EXPECT_THROW (NAME, f.execute (new_guy), AForm::GradeTooLowException);
}

template <typename T> static void execute_grade_equal_ok () {
    Bureaucrat b ("Bob", Info<T>::execute);
    T f ("target");
    f.beSigned (b);
    EXPECT_NO_THROW (NAME, f.execute (b));
}

template <typename T> static void execute_grade_one_below_throws () {
    Bureaucrat b ("Bob", Info<T>::execute + 1);
    T f ("target");
    f.beSigned (b);
    EXPECT_THROW (NAME, f.execute (b), AForm::GradeTooLowException);
}

static void shrubbery_creates_file () {
    std::remove ("target_shrubbery");
    ShrubberyCreationForm f ("target");
    f.beSigned (boss);
    EXPECT_NO_THROW (__FUNCTION__, f.execute (boss));
    std::ifstream ifs ("target_shrubbery");
    CHECK (std::string (__FUNCTION__) + "_exists", ifs.good ());
    CHECK (std::string (__FUNCTION__) + "_not_empty",
    ifs.peek () != std::ifstream::traits_type::eof ());
}

static void shrubbery_open_failure_throws () {
    ShrubberyCreationForm f ("this_does_not_exist/hahahaha");
    f.beSigned (boss);
    EXPECT_THROW (__FUNCTION__, f.execute (boss),
    ShrubberyCreationForm::CouldNotOpenFileException);
}

template <typename T> static void constructor_suite () {
    form_grades<T> ();
    form_name<T> ();
    form_not_signed_by_default<T> ();
    form_copy_keeps_signed<T> ();
    form_assign_copies_signed<T> ();
    form_delete_through_aform_pointer<T> ();
}

template <typename T> static void conditions_suite () {
    execute_unsigned_throws<T> ();
    execute_grade_too_low_throws<T> ();
    execute_grade_equal_ok<T> ();
    execute_grade_one_below_throws<T> ();
}

template <typename T> static void form_suite () {
    std::cout << std::endl << TITLE << std::endl;
    constructor_suite<T> ();
    conditions_suite<T> ();
}

static void shrubbery_suite () {
    std::cout << std::endl << upper (__FUNCTION__) << std::endl;
    shrubbery_creates_file ();
    shrubbery_open_failure_throws ();
}

int main (void) {
    form_suite<ShrubberyCreationForm> ();
    form_suite<RobotomyRequestForm> ();
    form_suite<PresidentialPardonForm> ();

    shrubbery_suite ();
}
