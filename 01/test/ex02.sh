#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/test_lib.sh"
cd "$HERE/../ex02" || exit 1

NAME=hit
SRCS="main.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks
summary
