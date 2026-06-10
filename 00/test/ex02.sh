#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/test_lib.sh"
FIX="$HERE/ex02"
cd "$HERE/../ex02" || exit 1

NAME=account
SRCS="Account.cpp tests.cpp"

check_file_exist Makefile $SRCS
check_makefile tests.cpp
check_norm Account.cpp

assert_log() {
	title=$1
	tmp_out=$(mktemp)
	tmp_exp=$(mktemp)
	./"$NAME" 2>&1 | cut -c 17- > "$tmp_out"
	cut -c 17- "$2" > "$tmp_exp"
	if diff -q "$tmp_out" "$tmp_exp" >/dev/null 2>&1; then
		_result ok "$title"
	else
		_result ko "$title" "$(diff "$tmp_exp" "$tmp_out" | head -8)"
	fi
	rm -f "$tmp_out" "$tmp_exp"
}

section "FUNCTIONAL"
assert_log "output matches reference log" "19920104_091532.log"
summary
