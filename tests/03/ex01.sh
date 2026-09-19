#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 03 ex01

NAME=scavTrap
SRCS="main.cpp ClapTrap.cpp ScavTrap.cpp"
HEADERS="ClapTrap.hpp ScavTrap.hpp"
LIBSRCS="ClapTrap.cpp ScavTrap.cpp"

check_file_exist Makefile $SRCS $HEADERS
check_makefile main.cpp
check_makefile_rules
check_header_rebuild ClapTrap.hpp
check_norm $SRCS $HEADERS
check_no_header_impl $HEADERS
check_headers_standalone $HEADERS
check_strict_compile $SRCS
check_leaks
check_ocf ClapTrap ScavTrap
run_capture
assert_rc "student main exits 0" 0
assert_ends_newline
check_snippet "ScavTrap derives publicly from ClapTrap (upcast works)" 'void f(ScavTrap &s) { ClapTrap &c = s; (void)c; }' ScavTrap.hpp
check_snippet "ScavTrap has guardGate()" 'void f(ScavTrap &s) { s.guardGate(); }' ScavTrap.hpp
run_harness "$FIX/harness.cpp" $LIBSRCS
