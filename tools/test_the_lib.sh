#!/usr/bin/env bash

NAME=../01/ex05/harl
. testlib/testlib.sh

section "ASSERT"
assert_stdout "test 1" "abc"

check_file_exist "$NAME"

check_makefile

check_norm ""

check_leaks

summary
