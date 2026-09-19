#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 02 ex03

NAME=bsp
SRCS="main.cpp Fixed.cpp Point.cpp bsp.cpp"
HEADERS="Fixed.hpp Point.hpp"
LIBSRCS="Fixed.cpp Point.cpp bsp.cpp"

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
check_ocf Point
# ex03 is built on the Fixed class of ex02: it must keep the whole public API
check_snippet "Fixed: 6 comparison operators (ex02 API kept)" \
	'void f(const Fixed &a, const Fixed &b) { (void)(a > b); (void)(a < b); (void)(a >= b); (void)(a <= b); (void)(a == b); (void)(a != b); }' Fixed.hpp
check_snippet "Fixed: 4 arithmetic operators" \
	'void f(const Fixed &a, const Fixed &b) { (void)(a + b); (void)(a - b); (void)(a * b); (void)(a / b); }' Fixed.hpp
check_snippet "Fixed: inc/dec (pre+post)" \
	'void f(Fixed &a) { ++a; a++; --a; a--; }' Fixed.hpp
check_snippet "Fixed: min/max 4 overloads" \
	'Fixed &(*a)(Fixed&, Fixed&) = &Fixed::min; const Fixed &(*b)(const Fixed&, const Fixed&) = &Fixed::min;
	 Fixed &(*c)(Fixed&, Fixed&) = &Fixed::max; const Fixed &(*d)(const Fixed&, const Fixed&) = &Fixed::max;' Fixed.hpp
check_snippet "Fixed: ctors int/float + toFloat/toInt + operator<<" \
	'void f() { Fixed a(1); Fixed b(1.5f); a.toFloat(); a.toInt(); std::cout << b; }' Fixed.hpp
check_snippet "Point: default ctor, (float,float) ctor, copy" \
	'void f() { Point a; Point b(1.5f, 2.5f); Point c(b); Point d; d = c; }' Point.hpp
check_snippet "Point: constructible from ints (implicit int->float)" \
	'void f() { Point a(1, 2); (void)a; }' Point.hpp
check_snippet "bsp signature: bool bsp(Point const, Point const, Point const, Point const)" \
	'bool bsp(Point const a, Point const b, Point const c, Point const point);
	 bool (*fp)(Point const, Point const, Point const, Point const) = &bsp;' Point.hpp
if grep -qE 'Fixed\s+const\s+_?x|const\s+Fixed\s+_?x' Point.hpp && grep -qE 'Fixed\s+const\s+_?y|const\s+Fixed\s+_?y' Point.hpp; then
	_result ok "Point: x and y are 'Fixed const' attributes"
else
	_result ko "Point: x and y are 'Fixed const' attributes" "not found in Point.hpp"
fi
if grep -nE '^\s*(public|private|protected)?\s*:?\s*(Fixed|float|int)\s+_?[xy]\s*;' Point.hpp | grep -vq const; then
	_result ko "Point: x/y not public" "non-const x/y exposed"
else
	_result ok "Point: no mutable x/y attribute"
fi
run_capture
assert_rc "student main exits 0" 0
assert_ends_newline
run_harness "$FIX/harness.cpp" $LIBSRCS
