#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/test_lib.sh"
cd "$HERE/../ex01" || exit 1

NAME=zombieHorde
SRCS="main.cpp Zombie.cpp Zombie.hpp zombieHorde.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
summary
