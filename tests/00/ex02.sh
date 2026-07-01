#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 00 ex02

NAME=account
SRCS="Account.cpp tests.cpp"

# section ex02
check_file_exist Makefile $SRCS
check_makefile tests.cpp
check_norm Account.cpp Account.hpp

# section "FUNCTIONAL"
assert_log_diff "output matches reference log" 19920104_091532.log

# summary
