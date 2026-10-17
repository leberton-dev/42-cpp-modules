#include <cassert>
#include <iostream>
#include <sstream>

#include "Bureaucrat.hpp"

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
}
