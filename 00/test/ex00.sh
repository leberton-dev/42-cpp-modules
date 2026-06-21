#!/bin/bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/testlib/testlib.sh"
cd "$HERE/../ex00" || exit 1

NAME=megaphone
SRCS="megaphone.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS

section "FUNCTIONAL"
assert_stdout "subject test 1" "SHHHHH.. I THINK THE STUDENTS ARE ASLEEP..." "shhhhh.. I think the students are asleep..."
assert_stdout "subject test 2" "DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF." Damnit " ! " "" "Sorry students, I thought this thing was off."
assert_stdout "subject test 3" "* LOUD AND UNBEARABLE FEEDBACK NOISE *"
assert_stdout "testing with one argument" "TEST NUMBER 4" "Test number 4"
assert_stdout "testing with multiple arguments" "TEST NUMBER FIVE YOU SEE ?" "Test " number " FIVE you see ?"
assert_stdout "empty arg" "* LOUD AND UNBEARABLE FEEDBACK NOISE *" ""
assert_stdout "already uppercase" "HELLO WORLD" "hello world"
assert_stdout "digits and punctuation" "HELLO123;:!?" "hello123;:!?"
assert_stdout "mixed digits and letters" "HELLO42OK" "hello42ok"

summary
