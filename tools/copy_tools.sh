#!/bin/bash

test_lib_src=tools/test_lib.sh

for m in 00 01; do
	test_lib_dest="$m/test/test_lib.sh"
	mkdir -p "$m/test"
	if [ -f "$test_lib_dest" ]; then
		rm -f "$test_lib_dest"
	fi
	cp "$test_lib_src" "$test_lib_dest"
done
