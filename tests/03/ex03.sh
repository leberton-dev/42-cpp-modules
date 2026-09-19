#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 03 ex03

NAME=diamondTrap
SRCS="main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp"
HEADERS="ClapTrap.hpp ScavTrap.hpp FragTrap.hpp DiamondTrap.hpp"
LIBSRCS="ClapTrap.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp"

check_file_exist Makefile $SRCS $HEADERS
check_makefile main.cpp
check_makefile_rules
check_header_rebuild ClapTrap.hpp
check_norm $SRCS $HEADERS
check_no_header_impl $HEADERS
check_headers_standalone $HEADERS
check_strict_compile $SRCS
check_leaks
check_ocf ClapTrap ScavTrap FragTrap DiamondTrap
run_capture
assert_rc "student main exits 0" 0
assert_ends_newline
check_snippet "DiamondTrap has whoAmI() + guardGate + highFivesGuys + attack + takeDamage (no ambiguity)" \
	'void f(DiamondTrap &d) { d.whoAmI(); d.guardGate(); d.highFivesGuys(); d.attack("t"); d.takeDamage(1u); d.beRepaired(1u); }' DiamondTrap.hpp
check_snippet "DiamondTrap upcasts to ScavTrap& and FragTrap& and ClapTrap& (virtual base => unambiguous)" \
	'void f(DiamondTrap &d) { ScavTrap &s = d; FragTrap &g = d; ClapTrap &c = d; (void)s; (void)g; (void)c; }' DiamondTrap.hpp
# variable named `_name`, same as ClapTrap's, private
if sed -n '/private:/,/};/p' DiamondTrap.hpp | grep -qE 'std::string\s+_name\s*;'; then
	_result ok "DiamondTrap: private attribute named exactly like ClapTrap's (_name)"
else
	_result ko "DiamondTrap: private attribute named exactly like ClapTrap's (_name)" "not found"
fi
if grep -qE 'virtual\s+public\s+ClapTrap|public\s+virtual\s+ClapTrap' ScavTrap.hpp FragTrap.hpp \
	&& [ "$(grep -cE 'virtual\s+public\s+ClapTrap|public\s+virtual\s+ClapTrap' ScavTrap.hpp FragTrap.hpp | grep -c ':1')" = 2 ]; then
	_result ok "ScavTrap and FragTrap inherit VIRTUALLY from ClapTrap"
else
	_result ko "ScavTrap and FragTrap inherit VIRTUALLY from ClapTrap" "virtual inheritance missing in ScavTrap.hpp or FragTrap.hpp"
fi
if grep -qE 'class\s+DiamondTrap\s*:\s*public\s+ScavTrap\s*,\s*public\s+FragTrap|class\s+DiamondTrap\s*:\s*public\s+FragTrap\s*,\s*public\s+ScavTrap' DiamondTrap.hpp; then
	_result ok "DiamondTrap inherits publicly from ScavTrap AND FragTrap"
else
	_result ko "DiamondTrap inherits publicly from ScavTrap AND FragTrap" "declaration not found"
fi
if grep -q -- '-Wshadow' Makefile; then _result ok "Makefile uses -Wshadow (subject hint)"; else _result ko "Makefile uses -Wshadow (subject hint)" "not in Makefile"; fi
run_harness "$FIX/harness.cpp" $LIBSRCS
