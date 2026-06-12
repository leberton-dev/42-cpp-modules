#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/test_lib.sh"
cd "$HERE/../ex03" || exit 1

NAME=violence
SRCS="main.cpp Weapon.cpp HumanA.cpp HumanB.cpp HumanA.hpp HumanB.hpp Weapon.hpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
summary
