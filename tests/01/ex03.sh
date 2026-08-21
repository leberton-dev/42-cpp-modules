#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 01 ex03

NAME=violence
SRCS="main.cpp Weapon.cpp HumanA.cpp HumanB.cpp HumanA.hpp HumanB.hpp Weapon.hpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
