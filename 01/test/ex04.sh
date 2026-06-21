#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/testlib/testlib.sh"
cd "$HERE/../ex04" || exit 1

NAME=mySed
SRCS="main.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks "Makefile" "NAME" "HAHA"
rm -f "Makefile.replace"
summary
