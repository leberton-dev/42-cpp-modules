#!/bin/bash

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && /usr/bin/pwd)"
. "$HERE/../lib.sh"
enter_exercise 00 ex01

NAME=phonebook
SRCS="main.cpp Contact.cpp PhoneBook.cpp Program.cpp"
HEADERS="Contact.hpp PhoneBook.hpp Program.hpp"

# section ex01
check_file_exist Makefile $SRCS
check_makefile main.cpp
check_norm $SRCS $HEADERS

# section "FUNCTIONAL"
assert_stdin "add a contact" "$FIX/input/valid_add.input" "$FIX/expected/valid_add.expected"
assert_stdin "truncate 10 chars"      "$FIX/input/valid_truncate_ten_chars.input" "$FIX/expected/valid_truncate_ten_chars.expected"
assert_stdin "truncate 11 chars"      "$FIX/input/valid_truncate_eleven_chars.input" "$FIX/expected/valid_truncate_eleven_chars.expected"
assert_stdin "direct exit"            "$FIX/input/valid_direct_exit.input"       "$FIX/expected/valid_direct_exit.expected"
assert_stdin "cancel exit"            "$FIX/input/valid_cancel_exit.input"       "$FIX/expected/valid_cancel_exit.expected"
assert_stdin "return from search"     "$FIX/input/valid_return_from_search.input" "$FIX/expected/valid_return_from_search.expected"
assert_stdin "replace 9th contact"    "$FIX/input/replace_ninth_contact.input"   "$FIX/expected/replace_ninth_contact.expected"
assert_stdin "empty phonebook search" "$FIX/input/invalid_empty_phonebook.input" "$FIX/expected/invalid_empty_phonebook.expected"
assert_stdin "invalid command"        "$FIX/input/invalid_command.input"         "$FIX/expected/invalid_command.expected"
assert_stdin "invalid search index"   "$FIX/input/invalid_search_index.input"    "$FIX/expected/invalid_search_index.expected"
assert_stdin "invalid exit command"   "$FIX/input/invalid_exit_command.input"    "$FIX/expected/invalid_exit_command.expected"

# summary
