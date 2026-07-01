#!/bin/bash

_get_title() {
	if [ $# -eq 2 ]; then
		echo "MODULE $1 - EXO $2"
	elif [ $# -eq 1 ]; then
		echo "MODULE $1"
	else
		echo "ALL MODULES"
	fi
}

if [ ! $# -eq 1 ] && [ ! $# -eq 2 ]; then
	echo "Usage: $0 <module> [<exo>]"
	exit 1
fi

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && /usr/bin/pwd)"
. "$HERE/lib.sh"
run_one() { . "$1"; }

if [ -n "$2" ]; then
	section "$(_get_title "$@")"
	run_one "$HERE/$1/ex$2.sh"
elif [ -n "$1" ]; then
	printf "$(_get_title "$@")\n"
	for f in "$HERE/$1"/ex*.sh; do
		section "$1/$(basename "$f")"
		run_one "$f"
	done
else
	for f in "$HERE"/*/ex*.sh; do run_one "$f"; done
fi
summary
exit $?

