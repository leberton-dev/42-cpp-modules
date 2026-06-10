#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/test_lib.sh"
cd "$HERE/../ex02" || exit 1

NAME=account
SRCS="Account.cpp tests.cpp"

check_file_exist Makefile $SRCS
check_makefile tests.cpp
check_norm Account.cpp Account.hpp

# assert_log_diff <title> <log_file>
assert_log_diff() {
	title=$1
	tmp=$(mktemp)
	./"$NAME" > "$tmp" 2>&1
	if diff <(cut -c 17- "$2") <(cut -c 17- "$tmp") >/dev/null 2>&1; then
		_result ok "$title"
	else
		_result ko "$title" "$(diff <(cut -c 17- "$2") <(cut -c 17- "$tmp") | head -8)"
	fi
	rm -f "$tmp"
}

section "FUNCTIONAL"
assert_log_diff "output matches reference log" 19920104_091532.log

summary
