#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 02 ex02

NAME=fixed
SRCS="main.cpp Fixed.cpp"
HEADERS="Fixed.hpp"
LIBSRCS="Fixed.cpp"

check_file_exist Makefile $SRCS $HEADERS
check_makefile main.cpp
check_makefile_rules
check_header_rebuild Fixed.hpp
check_norm $SRCS $HEADERS
check_no_header_impl $HEADERS
check_headers_standalone $HEADERS
check_strict_compile $SRCS
check_leaks
check_ocf Fixed
check_snippet "6 comparison operators exist (const)" \
	'void f(const Fixed &a, const Fixed &b) { (void)(a > b); (void)(a < b); (void)(a >= b); (void)(a <= b); (void)(a == b); (void)(a != b); }' Fixed.hpp
check_snippet "4 arithmetic operators exist (const)" \
	'void f(const Fixed &a, const Fixed &b) { (void)(a + b); (void)(a - b); (void)(a * b); (void)(a / b); }' Fixed.hpp
check_snippet "4 inc/dec operators exist" \
	'void f(Fixed &a) { ++a; a++; --a; a--; }' Fixed.hpp
check_snippet "pre-inc returns Fixed&, post-inc returns Fixed" \
	'void f(Fixed &a) { Fixed &r = ++a; Fixed p = a++; Fixed &r2 = --a; Fixed p2 = a--; (void)r; (void)p; (void)r2; (void)p2; }' Fixed.hpp
check_snippet "min/max overloaded on Fixed& AND const Fixed&" \
	'Fixed &(*a)(Fixed&, Fixed&) = &Fixed::min; const Fixed &(*b)(const Fixed&, const Fixed&) = &Fixed::min;
	 Fixed &(*c)(Fixed&, Fixed&) = &Fixed::max; const Fixed &(*d)(const Fixed&, const Fixed&) = &Fixed::max;' Fixed.hpp
assert_stdin "subject output, byte for byte" /dev/null "$FIX/subject.expected"
assert_ends_newline
run_harness "$FIX/harness.cpp" $LIBSRCS
