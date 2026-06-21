#!/usr/bin/env bash

_check_compiles() {
	if make re >/dev/null 2>&1; then
		_result ok "compiles"
	else
		_result ko "compiles" "make re returned non-zero"
	fi
}

_check_no_warnings() {
	out=$(make re 2>&1)
	if printf '%s' "$out" | grep -iqE 'warning:|error:'; then
		_result ko "no warnings"
	else
		_result ok "no warnings"
	fi
}

_check_relinking() {
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

_check_recompile() {
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

_check_clean() {
	make fclean >/dev/null 2>&1
	leftover=$(ls *.o "$NAME" 2>/dev/null)
	if [ -z "$leftover" ]; then
		_result ok "fclean removes binary + objects"
	else
		_result ko "fclean removes binary + objects" "leftover: $(echo $leftover | tr '\n' ' ')"
	fi
	make >/dev/null 2>&1
}


# check_makefile <source_files... >
#
# This is a section, multiple test to ensure compilation
# of makefile working as expected.
#
# 	source_files - all files needed for compilation
check_makefile() {
	section "MAKEFILE"
	_check_compiles
	_check_no_warnings
	_check_relinking
	_check_recompile "$1"
	_check_clean
}

