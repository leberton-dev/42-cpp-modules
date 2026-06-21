#!/usr/bin/env bash

HERE="$(dirname "${BASH_SOURCE[0]}")"
. "$HERE/testlib/testlib.sh"
cd "$HERE/../ex06" || exit 1

NAME=harlFilter
SRCS="main.cpp Harl.cpp"

check_file_exist Makefile $SRCS
check_makefile $SRCS
check_norm $SRCS
check_leaks "DEBUG"

section "ASSERT OUTPUT"

assert_stdout "empty" "[ Probably complaining about insignificant problems ]" ""
assert_stdout "subject" "[ Probably complaining about insignificant problems ]" "I am not sure how tired I am today..."
assert_stdout "debug" "[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!

[ INFO ]
I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!

[ WARNING ]
I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now." "DEBUG"

assert_stdout "info" "[ INFO ]
I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!

[ WARNING ]
I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now." "INFO"

assert_stdout "warning" "[ WARNING ]
I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now." "WARNING"

assert_stdout "error" "[ ERROR ]
This is unacceptable! I want to speak to the manager now." "ERROR"

summary
