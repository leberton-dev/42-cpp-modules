#!/bin/bash

NAME=megaphone
R='\033[0;31m'
G='\033[0;32m'
N='\033[0m'

run_test() {
	title=$1
	expected=$2
	shift 2

	actual=$(./"$NAME" "$@")
	if [ "$actual" = "$expected" ]; then
		printf "%-40s [${G}OK${N}]\n" "$title"
	else
		printf "%-40s [${R}KO${N}]\n" "$title"
		printf "    expected: '%s' - received: '%s'\n" "$expected" "$actual"
	fi
}

run_test "subject test 1" "SHHHHH.. I THINK THE STUDENTS ARE ASLEEP..." "shhhhh.. I think the students are asleep..."
run_test "subject test 2" "DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF." Damnit " ! " "" "Sorry students, I thought this thing was off."
run_test "subject test 3" "* LOUD AND UNBEARABLE FEEDBACK NOISE *"
run_test "testing with one argument" "TEST NUMBER 4" "Test number 4"
run_test "testing with multiple arguments" "TEST NUMBER FIVE YOU SEE ?" "Test " number " FIVE you see ?"
