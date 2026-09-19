#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 02 ex00

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

# --- subject main: same lines as the subject, order of the getRawBits/value lines is unspecified
run_capture
assert_rc "subject main exits 0" 0
assert_count "2x default constructor" "Default constructor called" 2
assert_count "1x copy constructor" "Copy constructor called" 1
assert_count "3x destructor" "Destructor called" 3
assert_count "3x getRawBits message" "getRawBits member function called" 3
assert_count "3x raw value 0" "0" 3
n=$(printf '%s' "$OUT" | grep -cxF "Copy assignment operator called")
if [ "$n" = 1 ] || [ "$n" = 2 ]; then _result ok "copy assignment message (1 or 2 times)"; else _result ko "copy assignment message (1 or 2 times)" "found $n"; fi
assert_ends_newline

run_harness "$FIX/harness.cpp" $LIBSRCS
