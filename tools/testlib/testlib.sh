#!/usr/bin/env bash

_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$_DIR/core.sh"
. "$_DIR/assert.sh"
. "$_DIR/files.sh"
. "$_DIR/makefile.sh"
. "$_DIR/norm.sh"
. "$_DIR/leaks.sh"
