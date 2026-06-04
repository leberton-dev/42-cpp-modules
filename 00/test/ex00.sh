#!/bin/bash

. "$(dirname "${BASH_SOURCE[0]}")/test_lib.sh"

NAME=megaphone
SRCS="megaphone.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS

section "FUNCTIONAL"
assert_output "subject test 1" "SHHHHH.. I THINK THE STUDENTS ARE ASLEEP..." "shhhhh.. I think the students are asleep..."
assert_output "subject test 2" "DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF." Damnit " ! " "" "Sorry students, I thought this thing was off."
assert_output "subject test 3" "* LOUD AND UNBEARABLE FEEDBACK NOISE *"
assert_output "testing with one argument" "TEST NUMBER 4" "Test number 4"
assert_output "testing with multiple arguments" "TEST NUMBER FIVE YOU SEE ?" "Test " number " FIVE you see ?"
assert_output "empty arg" "* LOUD AND UNBEARABLE FEEDBACK NOISE *" ""
assert_output "already uppercase" "HELLO WORLD" "hello world"
assert_output "digits and punctuation" "HELLO123;:!?" "hello123;:!?"
assert_output "mixed digits and letters" "HELLO42OK" "hello42ok"

summary
