#!/usr/bin/env bash

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

_check_forbidden() {
	_forbid '\b(printf|fprintf|sprintf|malloc|calloc|realloc|free)\s*\(' \
		"no forbidden functions" "$@"
}

_check_no_using_namespace() {
	_forbid 'using namespace|\bfriend\b' "no using namespace / friend" "$@"
}

_check_no_stl() {
	_forbid '#include <(vector|map|list|algorithm|set|stack|queue|deque)>' \
		"no STL containers / algorithms" "$@"
}

_check_include_guards() {
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

# check_norm <files_to_check...>
check_norm() {
	section "NORM"
	_check_forbidden "$@"
	_check_no_using_namespace "$@"
	_check_no_stl "$@"
	_check_include_guards "$@"
}
