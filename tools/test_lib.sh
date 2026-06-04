#!/bin/bash

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

_SECTION=''

_flush_section() {
	[ -z "$_SECTION" ] && return
	printf "    ${B}%s: %d passed, %d failed${N}\n\n" \
		"$_SECTION" "$_SEC_PASS" "$_SEC_FAIL"
}

section() {
	_flush_section
	_SECTION=$1
	_SEC_PASS=0
	_SEC_FAIL=0
	printf "${B}=== %s ===${N}\n" "$_SECTION"
}

summary() {
	_flush_section
	printf "${B}=== SUMMARY ===${N}\n"
	printf "Total: ${G}%d passed${N}, ${R}%d failed${N}\n" "$PASS" "$FAIL"
	[ "$FAIL" -eq 0 ]
}

assert_output() {
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


# === CHECK MAKEFILE ===

check_compiles() {
	if make re >/dev/null 2>&1; then
		_result ok "compiles"
	else
		_result ko "compiles" "make re returned non-zero"
	fi
}

check_no_warnings() {
	out=$(make re 2>&1)
	if printf '%s' "$out" | grep -iqE 'warning:|error:'; then
		_result ko "no warnings"
	else
		_result ok "no warnings"
	fi
}

check_relinking() {
	make re >/dev/null 2>&1
	before=$(stat -c %Y "$NAME")
	sleep 1
	make >/dev/null 2>&1
	after=$(stat -c %Y "$NAME")
	if [ "$before" = "$after" ]; then
		_result ok "no relinking"
	else
		_result ko "no relinking" "make relinked an up-to-date target"
	fi
}

check_recompile() {
	make >/dev/null 2>&1
	before=$(stat -c %Y "$NAME")
	sleep 1
	touch "$1"
	make >/dev/null 2>&1
	after=$(stat -c %Y "$NAME")
	if [ "$before" != "$after" ]; then
		_result ok "recompiles after change"
	else
		_result ko "recompiles after change" "source changed but binary not rebuilt"
	fi
}

check_clean() {
	make fclean >/dev/null 2>&1
	leftover=$(ls *.o "$NAME" 2>/dev/null)
	if [ -z "$leftover" ]; then
		_result ok "fclean removes binary + objects"
	else
		_result ko "fclean removes binary + objects" "leftover: $(echo $leftover | tr '\n' ' ')"
	fi
	make >/dev/null 2>&1
}

check_makefile() {
	section "MAKEFILE"
	check_compiles
	check_no_warnings
	check_relinking
	check_recompile "$1"
	check_clean
}

# === === === === === === === ===


check_file_exist() {
	section "FILES"
	for f in "$@"; do
		if [ -f "$f" ]; then
			_result ok "present: $f"
		else
			_result ko "present: $f" "file missing"
		fi
	done
}

# === CHECK NORM ===

_forbid() {
	pattern=$1
	label=$2
	shift 2
	if grep -nEq "$pattern" "$@" 2>/dev/null; then
		_result ko "$label" "$(grep -nE "$pattern" "$@" 2>/dev/null | head -1)"
	else
		_result ok "$label"
	fi
}

check_forbidden() {
	_forbid '\b(printf|fprintf|sprintf|malloc|calloc|realloc|free)\b' \
		"no forbidden functions" "$@"
}

check_no_using_namespace() {
	_forbid 'using namespace|\bfriend\b' "no using namespace / friend" "$@"
}

check_no_stl() {
	_forbid '#include <(vector|map|list|algorithm|set|stack|queue|deque)>' \
		"no STL containers / algorithms" "$@"
}

check_include_guards() {
	for f in "$@"; do
		case "$f" in
			*.hpp) ;;
			*) continue ;;
		esac
		if grep -q '#ifndef\|#pragma once' "$f"; then
			_result ok "include guard: $f"
		else
			_result ko "include guard: $f" "no #ifndef / #pragma once"
		fi
	done
}

check_norm() {
	section "NORM"
	check_forbidden "$@"
	check_no_using_namespace "$@"
	check_no_stl "$@"
	check_include_guards "$@"
}

# === CHECK STDIN ===

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
