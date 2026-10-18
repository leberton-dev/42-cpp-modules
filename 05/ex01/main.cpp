#include <cassert>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "Bureaucrat.hpp"
#include "Form.hpp"

static void ok (const std::string msg) {
    std::cout << "[" << "\033[0;32m" << "OK" << "\033[0m" << "] ";
    std::cout << msg << std::endl;
}

static void ko (const std::string msg) {
    std::cout << "[" << "\033[0;31m" << "KO" << "\033[0m" << "] ";
    std::cout << msg << std::endl;
}

static void constructor_valid_highest (void) {
    Bureaucrat b ("Bob", 1);
    assert (b.getGrade () == 1);
    ok ("constructor_valid_highest");
}

static void constructor_valid_lowest (void) {
    Bureaucrat b ("Bob", 150);
    assert (b.getGrade () == 150);
    ok ("constructor_valid_lowest");
}

static void constructor_valid_middle (void) {
    Bureaucrat b ("Bob", 69);
    assert (b.getGrade () == 69);
    ok ("constructor_valid_middle");
}

static void constructor_too_high_zero (void) {
    try {
        Bureaucrat b ("Bob", 0);
        assert (false);
    } catch (Bureaucrat::GradeTooHighException& e) {
        ok ("constructor_too_high_zero");
    } catch (Bureaucrat::GradeTooLowException& e) {
        std::string s = "constructor_too_high_zero: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void constructor_too_low_151 (void) {
    try {
        Bureaucrat b ("Bob", 151);
        assert (false && "[KO] constructor_too_low_151: should have thrown");
    } catch (Bureaucrat::GradeTooLowException& e) {
        ok ("constructor_too_low_151");
    } catch (Bureaucrat::GradeTooHighException& e) {
        std::string s = "constructor_too_low_151: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void constructor_too_high_negative (void) {
    try {
        Bureaucrat b ("Bob", -69);
        assert (false && "[KO] constructor_too_high_negative");
    } catch (Bureaucrat::GradeTooHighException& e) {
        ok ("constructor_too_high_negative");
    } catch (Bureaucrat::GradeTooLowException& e) {
        std::string s = "constructor_too_high_negative: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void increment_basic (void) {
    Bureaucrat b ("Bob", 3);
    b.gradeIncrement ();
    assert (b.getGrade () == 2);
    ok ("increment_basic");
}

static void decrement_basic (void) {
    Bureaucrat b ("Bob", 3);
    b.gradeDecrement ();
    assert (b.getGrade () == 4);
    ok ("decrement_basic");
}

static void increment_at_highest (void) {
    Bureaucrat b ("Bob", 1);
    try {
        b.gradeIncrement ();
        assert (false && "[KO] increment_at_highest: should have thrown");
    } catch (Bureaucrat::GradeTooHighException& e) {
        ok ("increment_at_highest");
    } catch (Bureaucrat::GradeTooLowException& e) {
        std::string s = "increment_at_highest: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void decrement_at_lowest (void) {
    Bureaucrat b ("Bob", 150);
    try {
        b.gradeDecrement ();
        assert (false && "[KO] decrement_at_lowest: should have thrown");
    } catch (Bureaucrat::GradeTooLowException& e) {
        ok ("decrement_at_lowest");
    } catch (Bureaucrat::GradeTooHighException& e) {
        std::string s = "decrement_at_lowest: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void increment_throw_keeps_grade (void) {
    Bureaucrat b ("Bob", 1);
    try {
        b.gradeIncrement ();
        assert (false && "[KO] increment_throw_keeps_grade: should have thrown");
    } catch (std::exception& e) {
    }
    assert (b.getGrade () == 1);
    ok ("increment_throw_keeps_grade");
}

static void copy_constructor (void) {
    Bureaucrat b ("Bob", 1);
    Bureaucrat b2 (b);
    assert (b.getGrade () == b2.getGrade ());
    assert (b.getName () == b2.getName ());
    ok ("copy_constructor");
}

static void copy_independant (void) {
    Bureaucrat b ("Bob", 1);
    Bureaucrat b2 (b);
    b.gradeDecrement ();
    assert (b2.getGrade () == 1);
    ok ("copy_independant");
}

static void assign_operator (void) {
    Bureaucrat b ("Bob", 1);
    Bureaucrat a ("Alice", 69);
    a = b;
    assert (a.getGrade () == 1);
    ok ("assign_operator");
}

static void ostream_format (void) {
    Bureaucrat b ("Bob", 1);
    std::ostringstream oss;
    oss << b;
    assert (oss.str () == "Bob, bureaucrat grade 1.");
    ok ("ostream_format");
}


static void form_constructor_valid (void) {
    Form f ("Form1", 50, 10);
    assert (f.getGradeSign () == 50);
    assert (f.getGradeExecute () == 10);
    ok ("form_constructor_valid");
}

static void form_constructor_valid_limits (void) {
    Form f ("Form1", 1, 150);
    assert (f.getGradeSign () == 1);
    assert (f.getGradeExecute () == 150);
    ok ("form_constructor_valid_limits");
}

static void form_constructor_sign_too_high_zero (void) {
    try {
        Form f ("Form1", 0, 69);
    } catch (Form::GradeTooHighException& e) {
        ok ("form_constructor_sign_too_high_zero");
    } catch (Form::GradeTooLowException& e) {
        std::string s =
        "form_constructor_sign_too_high_zero: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void form_constructor_sign_too_low_151 (void) {
    try {
        Form f ("Form1", 151, 69);
    } catch (Form::GradeTooLowException& e) {
        ok ("form_constructor_sign_too_low_151");
    } catch (Form::GradeTooHighException& e) {
        std::string s = "form_constructor_sign_too_low_151: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void form_constructor_execute_too_high_zero (void) {
    try {
        Form f ("Form1", 69, 0);
    } catch (Form::GradeTooHighException& e) {
        ok ("form_constructor_execute_too_high_zero");
    } catch (Form::GradeTooLowException& e) {
        std::string s =
        "form_constructor_execute_too_high_zero: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void form_constructor_execute_too_low_151 (void) {
    try {
        Form f ("Form1", 69, 151);
    } catch (Form::GradeTooLowException& e) {
        ok ("form_constructor_execute_too_low_151");
    } catch (Form::GradeTooHighException& e) {
        std::string s =
        "form_constructor_execute_too_low_151: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void form_constructor_not_signed_by_default (void) {
    Form f ("Form1", 69, 42);
    assert (f.getSigned () == false);
    ok ("form_constructor_not_signed_by_default");
}

static void form_copy_constructor (void) {
    Form a ("f1", 42, 69);
    Form b (a);
    assert (a.getName () == b.getName ());
    assert (a.getSigned () == b.getSigned ());
    assert (a.getGradeSign () == b.getGradeSign ());
    assert (a.getGradeExecute () == b.getGradeExecute ());
    ok ("form_copy_constructor");
}

static void form_copy_keeps_signed (void) {
    Form a ("f1", 42, 69);
    Form b (a);
    Bureaucrat bob ("Bob", 1);
    a.beSigned (bob);
    assert (b.getSigned () == false);
    ok ("form_copy_keeps_signed");
}

static void form_assign_operator_copies_signed (void) {
    Form a ("f1", 42, 69);
    Form b ("f2", 33, 54);
    Bureaucrat bob ("Bob", 1);
    a.beSigned (bob);
    b = a;
    assert (b.getSigned () == a.getSigned ());
    ok ("form_assign_operator_copies_signed");
}

static void form_assign_operator_keeps_name_and_grades (void) {
    Form a ("f1", 42, 69);
    Form b ("f2", 33, 54);
    Bureaucrat bob ("Bob", 1);
    a.beSigned (bob);
    b = a;
    assert (b.getName () == "f2");
    assert (b.getGradeSign () == 33);
    assert (b.getGradeExecute () == 54);
    ok ("form_assign_operator_keeps_name_and_grades");
}

static void form_be_signed_grade_higher (void) {
    Bureaucrat b ("Bob", 1);
    Form f ("f1", 50, 50);
    f.beSigned (b);
    assert (f.getSigned () == true);
    ok ("form_be_signed_grade_higher");
}

static void form_be_signed_grade_equal (void) {
    Bureaucrat b ("Bob", 50);
    Form f ("f1", 50, 50);
    f.beSigned (b);
    assert (f.getSigned () == true);
    ok ("form_be_signed_grade_equal");
}

static void form_be_signed_grade_too_low (void) {
    Bureaucrat b ("Bob", 100);
    Form f ("f1", 50, 50);
    try {
        f.beSigned (b);
        assert (false && "[KO] should have thrown");
    } catch (Form::GradeTooLowException& e) {
        ok ("form_be_signed_grade_too_low");
    } catch (Form::GradeTooHighException& e) {
        std::string s = "form_be_signed_grade_too_low: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void form_be_signed_fail_stays_unsigned (void) {
    Bureaucrat b ("Bob", 100);
    Form f ("f1", 50, 50);
    try {
        f.beSigned (b);
        assert (false && "[KO] should have thrown");
    } catch (Form::GradeTooLowException& e) {
        assert (f.getSigned () == false);
        ok ("form_be_signed_grade_too_low");
    } catch (Form::GradeTooHighException& e) {
        std::string s = "form_be_signed_grade_too_low: wrong exception: ";
        s.append (e.what ());
        ko (s);
    }
}

static void form_be_signed_twice (void) {
    Bureaucrat b ("Bob", 1);
    Form f ("f1", 10, 5);
    f.beSigned (b);
    assert (f.getSigned () == true);
    f.beSigned (b);
    assert (f.getSigned () == true);
}

static void form_ostream_format (void) {
    Form f ("f1", 50, 25);
    std::ostringstream oss;
    oss << f;
    assert (oss.str () == "f1, signed 0, grade sign 50, grade execute 25");
    ok ("ostream_format");
}

static void sign_form_success_ouput (void) {
    Bureaucrat b ("Bob", 24);
    Form f ("f1", 103, 69);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf (oss.rdbuf ());
    b.signForm (f);
    std::cout.rdbuf (old);

    assert (oss.str () == "Bob signed f1\n");
    ok ("sign_form_success_ouput");
}

static void sign_form_success_sets_signed (void) {
    Bureaucrat b ("Bob", 24);
    Form f ("f1", 103, 69);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf (oss.rdbuf ());
    b.signForm (f);
    std::cout.rdbuf (old);

    assert (f.getSigned () == true);
    ok ("sign_form_success_output");
}

static void sign_form_fail_output (void) {
    Bureaucrat b ("Bob", 104);
    Form f ("f1", 103, 69);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf (oss.rdbuf ());
    b.signForm (f);
    std::cout.rdbuf (old);

    assert (oss.str () == "Bob couldn't sign f1 because Grade is too low.\n");
    ok ("sign_form_fail_output");
}

static void sign_form_fail_no_throw (void) {
    Bureaucrat b ("Bob", 104);
    Form f ("f1", 103, 42);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf (oss.rdbuf ());

    try {
        b.signForm (f);
        std::cout.rdbuf (old);
        ok ("sign_form_fail_no_throw");
    } catch (std::exception& e) {
        ko ("sign_form_fail_no_throw, caught exception");
    }
}

static void sign_form_fail_stays_unchanged (void) {
    Bureaucrat b ("Bob", 104);
    Form f ("f1", 103, 42);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf (oss.rdbuf ());
    b.signForm (f);
    std::cout.rdbuf (old);
    assert (f.getSigned () == false);
    ok ("sign_form_fail_stays_unchanged");
}

int main (void) {
    constructor_valid_highest ();
    constructor_valid_lowest ();
    constructor_valid_middle ();
    constructor_too_high_zero ();
    constructor_too_low_151 ();
    constructor_too_high_negative ();
    increment_basic ();
    decrement_basic ();
    increment_at_highest ();
    decrement_at_lowest ();
    increment_throw_keeps_grade ();
    copy_constructor ();
    copy_independant ();
    assign_operator ();
    ostream_format ();

    // Form: constructor
    form_constructor_valid ();
    form_constructor_valid_limits ();
    form_constructor_sign_too_high_zero ();
    form_constructor_sign_too_low_151 ();
    form_constructor_execute_too_high_zero ();
    form_constructor_execute_too_low_151 ();
    form_constructor_not_signed_by_default ();

    // Form: copy
    form_copy_constructor ();
    form_copy_keeps_signed ();
    form_assign_operator_copies_signed ();
    form_assign_operator_keeps_name_and_grades ();

    // Form: beSigned
    form_be_signed_grade_higher ();
    form_be_signed_grade_equal ();
    form_be_signed_grade_too_low ();
    form_be_signed_fail_stays_unsigned ();
    form_be_signed_twice ();

    form_ostream_format ();

    // Bureaucrat: signForm
    sign_form_success_ouput ();
    sign_form_success_sets_signed ();
    sign_form_fail_output ();
    sign_form_fail_no_throw ();
    sign_form_fail_stays_unchanged ();
}
