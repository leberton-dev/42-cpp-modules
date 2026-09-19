#!/bin/bash

# include guard
[ -n "$_LIB_LOADED" ] && return 0
_LIB_LOADED=1

# deactivate colors if the exit is not a terminal
if [ -t 1 ]; then
	R='\033[0;31m'; G='\033[0;32m'; Y='\033[0;33m'; B='\033[1;34m'; N='\033[0m'
else
	R=''; G=''; Y=''; B=''; N=''
fi

_LIB_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$_LIB_DIR/.." && pwd)"

enter_exercise() {
	FIX="$_LIB_DIR/$1/$2"
	cd "$REPO_ROOT/$1/$2" || exit 1
}

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
	# section "MAKEFILE"
	check_compiles
	check_no_warnings
	check_relinking
	check_recompile "$1"
	check_clean
}

# === === === === === === === ===


check_file_exist() {
	# section "FILES"
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
	_forbid '\b(printf|fprintf|sprintf|malloc|calloc|realloc|free)\s*\(' \
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
	# section "NORM"
	check_forbidden "$@"
	check_no_using_namespace "$@"
	check_no_stl "$@"
	check_include_guards "$@"
}

# === CHECK LEAKS ===

check_leaks() {
	if valgrind -q --leak-check=full --error-exitcode=1 ./"$NAME" "$@" >/dev/null 2>&1; then
		_result ok "no leaks"
	else
		_result ko "no leaks" "valgrind found leaks/errors"
	fi
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


# === EXTRA CHECKS (modules 02+) ===

# every header must compile alone, and twice in a row (include guards)
check_headers_standalone() {
	for h in "$@"; do
		case "$h" in *.hpp) ;; *) continue ;; esac
		if printf '#include "%s"\n#include "%s"\n' "$h" "$h" \
			| c++ -Wall -Wextra -Werror -std=c++98 -fsyntax-only -x c++ -I. - >/dev/null 2>&1; then
			_result ok "standalone + double inclusion: $h"
		else
			_result ko "standalone + double inclusion: $h" "header does not compile alone / twice"
		fi
	done
}

# "any function implementation in a header means 0" (except templates)
check_no_header_impl() {
	for h in "$@"; do
		case "$h" in *.hpp) ;; *) continue ;; esac
		if grep -nE '\)\s*(const)?\s*\{' "$h" >/dev/null 2>&1; then
			_result ko "no implementation in header: $h" "$(grep -nE '\)\s*(const)?\s*\{' "$h" | head -1)"
		else
			_result ok "no implementation in header: $h"
		fi
	done
}

# check_ocf <Class> : the four canonical members are declared in Class.hpp
check_ocf() {
	h="$1.hpp"
	c="$1"
	_ocf_one "default constructor" "$h" "(^|[^~[:alnum:]_])$c\s*\(\s*(void)?\s*\)\s*;"
	_ocf_one "copy constructor"    "$h" "$c\s*\(\s*(const\s+)?$c\s*&[^)]*\)\s*;|$c\s*\(\s*$c\s+const\s*&[^)]*\)\s*;"
	_ocf_one "copy assignment"     "$h" "operator\s*=\s*\("
	_ocf_one "destructor"          "$h" "~$c\s*\(\s*(void)?\s*\)"
}
_ocf_one() {
	if grep -qE "$3" "$2" 2>/dev/null; then
		_result ok "OCF $1: $2"
	else
		_result ko "OCF $1: $2" "not found"
	fi
}

# strict compile: pedantic C++98, -Wshadow, and clang++ (if any)
check_strict_compile() {
	for f in "$@"; do
		case "$f" in *.cpp) ;; *) continue ;; esac
		out=$(c++ -Wall -Wextra -Werror -std=c++98 -pedantic -fsyntax-only "$f" 2>&1)
		if [ -z "$out" ]; then
			_result ok "-pedantic c++98: $f"
		else
			_result ko "-pedantic c++98: $f" "$(printf '%s' "$out" | grep -m1 -E 'error')"
		fi
		out=$(c++ -Wall -Wextra -Werror -Wshadow -std=c++98 -fsyntax-only "$f" 2>&1)
		if [ -z "$out" ]; then
			_result ok "-Wshadow: $f"
		else
			_result ko "-Wshadow: $f" "$(printf '%s' "$out" | grep -m1 -E 'error')"
		fi
		if command -v clang++ >/dev/null 2>&1; then
			out=$(clang++ -Wall -Wextra -Werror -std=c++98 -fsyntax-only "$f" 2>&1)
			if [ -z "$out" ]; then
				_result ok "clang++ c++98: $f"
			else
				_result ko "clang++ c++98: $f" "$(printf '%s' "$out" | grep -m1 -E 'error')"
			fi
		fi
	done
}

# Makefile must use the 3 mandatory flags and export the 4 mandatory rules
check_makefile_rules() {
	for flag in -Wall -Wextra -Werror -std=c++98; do
		if grep -q -- "$flag" Makefile; then
			_result ok "Makefile flag $flag"
		else
			_result ko "Makefile flag $flag" "missing"
		fi
	done
	for r in all clean fclean re; do
		if make -n "$r" >/dev/null 2>&1; then
			_result ok "Makefile rule: $r"
		else
			_result ko "Makefile rule: $r" "make -n $r failed"
		fi
	done
}

# touching a header must trigger a rebuild
check_header_rebuild() {
	make >/dev/null 2>&1
	before=$(stat -c %Y "$NAME")
	sleep 1
	touch "$1"
	make >/dev/null 2>&1
	after=$(stat -c %Y "$NAME")
	if [ "$before" != "$after" ]; then
		_result ok "rebuilds after header change ($1)"
	else
		_result ko "rebuilds after header change ($1)" "header touched but binary not rebuilt"
	fi
}

# run the binary once: sets OUT (stdout+stderr) and RC
run_capture() {
	OUT=$(./"$NAME" "$@" 2>&1; echo "rc=$?")
	RC=${OUT##*rc=}
	OUT=${OUT%rc=*}
}

assert_rc() {
	if [ "$RC" = "$2" ]; then _result ok "$1"; else _result ko "$1" "rc=$RC, expected $2"; fi
}

# assert_count <title> <exact line> <n> : number of lines of $OUT equal to <line>
assert_count() {
	n=$(printf '%s' "$OUT" | grep -cxF -- "$2")
	if [ "$n" = "$3" ]; then _result ok "$1"; else _result ko "$1" "'$2' appears $n times, expected $3"; fi
}

# assert_count_sub <title> <substring> <n> : number of lines containing <substring>
assert_count_sub() {
	n=$(printf '%s' "$OUT" | grep -cF -- "$2")
	if [ "$n" = "$3" ]; then _result ok "$1"; else _result ko "$1" "'$2' appears in $n lines, expected $3"; fi
}

# every stdout line must end with '\n' (i.e. the last byte is a newline)
assert_ends_newline() {
	if [ "$(./"$NAME" 2>/dev/null | tail -c1 | od -An -c | tr -d ' ')" = '\n' ]; then
		_result ok "output ends with newline"
	else
		_result ko "output ends with newline" "last byte is not \\n"
	fi
}

# check_snippet <title> <code> <header...> : the snippet must compile (-fsyntax-only, c++98)
check_snippet() {
	title=$1; code=$2; shift 2
	{ for h in "$@"; do printf '#include "%s"\n' "$h"; done; printf '%s\n' "$code"; } \
		| c++ -Wall -Wextra -Werror -std=c++98 -fsyntax-only -x c++ -I. - >/dev/null 2>&1
	if [ $? -eq 0 ]; then _result ok "$title"; else _result ko "$title" "snippet does not compile"; fi
}

# run_harness <harness.cpp> <sources...>
# compiles the harness against the student's sources (ASan + UBSan) and turns
# each "@@OK<TAB>name" / "@@KO<TAB>name<TAB>detail" line of stderr into a result.
run_harness() {
	h=$1; shift
	bin=$(mktemp); err=$(mktemp); cerr=$(mktemp)
	if ! c++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address,undefined \
		-I. -I"$FIX" -I"$FIX/.." -I"$_LIB_DIR" "$h" "$@" -o "$bin" 2>"$cerr"; then
		_result ko "harness compiles" "$(grep -m1 -E 'error' "$cerr")"
		rm -f "$bin" "$err" "$cerr"
		return
	fi
	"$bin" >/dev/null 2>"$err"
	rc=$?
	while IFS="$(printf '\t')" read -r st name detail; do
		case "$st" in
			@@OK) _result ok "$name" ;;
			@@KO) _result ko "$name" "$detail" ;;
		esac
	done < <(grep '^@@' "$err")
	if grep -qE 'runtime error|Sanitizer' "$err"; then
		_result ko "sanitizers clean" "$(grep -m1 -E 'runtime error|Sanitizer' "$err")"
	else
		_result ok "sanitizers clean"
	fi
	if [ "$rc" -ne 0 ]; then
		_result ko "harness exit status" "rc=$rc (crash / abort)"
	fi
	rm -f "$bin" "$err" "$cerr"
}
