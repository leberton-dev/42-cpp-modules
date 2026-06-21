#!/usr/bin/env bash

_check_no_leaks() {
	if valgrind -q --leak-check=full --error-exitcode=1 ./"$NAME" "$@" >/dev/null 2>&1; then
		_result ok "no leaks"
	else
		_result ko "no leaks" "valgrind found leaks/errors"
	fi
}

# check_leaks <program_args... >
#
# This is a section, checking for leaks with valgrind.
check_leaks() {
	section "LEAKS"
	_check_no_leaks "$@"
}
