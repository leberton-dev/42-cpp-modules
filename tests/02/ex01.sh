#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 02 ex01

NAME=fixed
SRCS="main.cpp Fixed.cpp"
HEADERS="Fixed.hpp"
LIBSRCS="Fixed.cpp"

check_file_exist Makefile $SRCS $HEADERS
check_makefile main.cpp
check_makefile_rules
check_header_rebuild Fixed.hpp
check_norm $SRCS $HEADERS
check_no_header_impl $HEADERS
check_headers_standalone $HEADERS
check_strict_compile $SRCS
check_leaks
check_ocf Fixed
assert_stdin "subject output, byte for byte" /dev/null "$FIX/subject.expected"
assert_ends_newline
run_harness "$FIX/harness.cpp" $LIBSRCS
