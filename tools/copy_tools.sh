#!/bin/bash

test_lib_src="tools/testlib"
test_lib_dest="$1/test/testlib"

mkdir -p "$1/test"
if [ -d "$test_lib_dest" ]; then
	rm -rf "$test_lib_dest"
fi
cp -r "$test_lib_src" "$test_lib_dest"

# for m in 00 01; do
# 	test_lib_dest="$m/test/test_lib.sh"
# 	mkdir -p "$m/test"
# 	if [ -f "$test_lib_dest" ]; then
# 		rm -f "$test_lib_dest"
# 	fi
# 	cp "$test_lib_src" "$test_lib_dest"
# done
