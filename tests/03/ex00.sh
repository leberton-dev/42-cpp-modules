#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 03 ex00

NAME=clapTrap
SRCS="main.cpp ClapTrap.cpp"
HEADERS="ClapTrap.hpp"
LIBSRCS="ClapTrap.cpp"

check_file_exist Makefile $SRCS $HEADERS
check_makefile main.cpp
check_makefile_rules
check_header_rebuild ClapTrap.hpp
check_norm $SRCS $HEADERS
check_no_header_impl $HEADERS
check_headers_standalone $HEADERS
check_strict_compile $SRCS
check_leaks
check_ocf ClapTrap
run_capture
assert_rc "student main exits 0" 0
assert_ends_newline
# private attributes (subject: "private attributes")
if sed -n '/private:/,$p' ClapTrap.hpp | grep -q '_name'; then _result ok "ClapTrap: attributes are private"; else _result ko "ClapTrap: attributes are private" "no private: section with _name"; fi
check_snippet "ClapTrap(std::string) constructor + attack/takeDamage(unsigned)/beRepaired(unsigned)" \
	'void f(ClapTrap &c) { c.attack("t"); c.takeDamage(1u); c.beRepaired(1u); }' ClapTrap.hpp
check_snippet "takeDamage/beRepaired take unsigned int (exact signature)" \
	'void (ClapTrap::*a)(unsigned int) = &ClapTrap::takeDamage; void (ClapTrap::*b)(unsigned int) = &ClapTrap::beRepaired; void (ClapTrap::*c)(const std::string&) = &ClapTrap::attack;' ClapTrap.hpp
run_harness "$FIX/harness.cpp" $LIBSRCS
