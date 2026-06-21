#!/bin/usr/env bash

# assert_stdout <title> <expected> <program_args>
assert_stdout() {
	title=$1
	expected=$2
	shift 2

	actual=$(./"$NAME" "$@")
	if [ "$actual" = "$expected" ]; then
		_result ok "$title"
	else
		_result ko "$title" "expected: '$expected' - received: '$actual'"
	fi
}

# assert_stdin <title> <input_file> <expected_file>
assert_stdin() {
	title=$1
	tmp=$(mktemp)
	./"$NAME" < "$2" > "$tmp" 2>&1
	if diff -q "$tmp" "$3" >/dev/null 2>&1; then
		_result ok "$title"
	else
		_result ko "$title"  "$(diff "$tmp" "$3" | head -8 )"
	fi
	rm -f "$tmp"
}
