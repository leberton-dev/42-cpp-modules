#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/testlib/testlib.sh"
cd "$HERE/../ex00" || exit 1

NAME=zomb
SRCS="main.cpp Zombie.cpp Zombie.hpp newZombie.cpp randomChump.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
summary
