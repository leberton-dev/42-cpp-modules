#!/usr/bin/env bash

# check_file_exist <files... >
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
