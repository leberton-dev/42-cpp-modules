#!/usr/bin/env bash

# deactivate colors if the exit is not a terminal
if [ -t 1 ]; then
	R='\033[0;31m'; G='\033[0;32m'; Y='\033[0;33m'; B='\033[1;34m'; N='\033[0m'
else
	R=''; G=''; Y=''; B=''; N=''
fi

PASS=0
FAIL=0
_SEC_PASS=0
_SEC_FAIL=0
_SECTION=''

_result() {
	if [ "$1" = "ok" ]; then
		printf "%-42s [${G}OK${N}]\n" "$2"
		PASS=$((PASS + 1)); _SEC_PASS=$((_SEC_PASS + 1))
	else
		printf "%-42s [${R}KO${N}]\n" "$2"
		[ -n "$3" ] && printf "    ${Y}%s${N}\n" "$3"
		FAIL=$((FAIL + 1)); _SEC_FAIL=$((_SEC_FAIL + 1))
	fi
}

_flush_section() {
	[ -z "$_SECTION" ] && return
	printf "    ${B}%s: %d passed, %d failed${N}\n\n" \
		"$_SECTION" "$_SEC_PASS" "$_SEC_FAIL"
}

# section <name>
#
# Creates a new session for tests, displaying a header.
#
# If present, it flushes the previous section, displaying
# name and the amount of passed and failed tests.
section() {
    _flush_section
    _SECTION=$1
    _SEC_PASS=0
    _SEC_FAIL=0
    printf "${B}=== %s ===${N}\n" "$_SECTION"
}

# summary
#
# Displays a summary for all tests produced.
#
# If present, it flushes the previous section, displaying
# name and the amount of passed and failed tests.
summary() {
	_flush_section
	printf "${B}=== SUMMARY ===${N}\n"
	printf "Total: ${G}%d passed${N}, ${R}%d failed${N}\n" "$PASS" "$FAIL"
	[ "$FAIL" -eq 0 ]
}

