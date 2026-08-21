#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
enter_exercise 01 ex05

NAME=harl
SRCS="main.cpp Harl.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks "DEBUG"

section "ASSERT OUTPUT"
assert_output "debug" "[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" "DEBUG"
assert_output "info" "[ INFO ]
I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" "INFO"
assert_output "warning" "[ WARNING ]
I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." "WARNING"
assert_output "error" "[ ERROR ]
This is unacceptable! I want to speak to the manager now." "ERROR"
assert_output "empty" "" ""
assert_output "wrong level" "" "UNKNOWN"
