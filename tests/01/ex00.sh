#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 01 ex00

NAME=zomb
SRCS="main.cpp Zombie.cpp Zombie.hpp newZombie.cpp randomChump.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
