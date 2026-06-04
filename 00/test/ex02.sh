#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")" 
. "$HERE/test_lib.sh"
cd "$HERE/../ex02" || exit 1

NAME=account
SRCS="Account.cpp tests.cpp"

check_file_exist Makefile $SRCS
check_makefile tests.cpp
check_norm $SRCS Account.hpp

section "FUNCTIONAL"
assert_log_diff "output matches log" 19920104_091532.log
