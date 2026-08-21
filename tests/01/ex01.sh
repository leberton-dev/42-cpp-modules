#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 01 ex01

NAME=zombieHorde
SRCS="main.cpp Zombie.cpp Zombie.hpp zombieHorde.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
