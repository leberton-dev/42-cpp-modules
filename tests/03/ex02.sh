#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 03 ex02

NAME=fragTrap
SRCS="main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp"
HEADERS="ClapTrap.hpp ScavTrap.hpp FragTrap.hpp"
LIBSRCS="ClapTrap.cpp ScavTrap.cpp FragTrap.cpp"

check_file_exist Makefile $SRCS $HEADERS
check_makefile main.cpp
check_makefile_rules
check_header_rebuild ClapTrap.hpp
check_norm $SRCS $HEADERS
check_no_header_impl $HEADERS
check_headers_standalone $HEADERS
check_strict_compile $SRCS
check_leaks
check_ocf ClapTrap ScavTrap FragTrap
run_capture
assert_rc "student main exits 0" 0
assert_ends_newline
check_snippet "FragTrap derives publicly from ClapTrap (upcast works)" 'void f(FragTrap &s) { ClapTrap &c = s; (void)c; }' FragTrap.hpp
check_snippet "FragTrap has highFivesGuys(void)" 'void f(FragTrap &s) { s.highFivesGuys(); }' FragTrap.hpp
check_snippet "ScavTrap from ex01 still works next to FragTrap" 'void f(ScavTrap &s, FragTrap &g) { s.guardGate(); g.highFivesGuys(); }' ScavTrap.hpp FragTrap.hpp
# ScavTrap.hpp and FragTrap.hpp cannot be included together in ex02 if they share macro names,
# so ClapTrap+ScavTrap and ClapTrap+FragTrap are exercised by two separate harness programs.
run_harness "$FIX/harness.cpp" $LIBSRCS
run_harness "$FIX/harness_frag.cpp" $LIBSRCS
