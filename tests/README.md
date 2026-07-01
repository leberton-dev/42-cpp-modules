# READ THIS IS IMPORTANT

Hey thanks for reading.
So, a few things to implement new tests for the cpp modules:

## a. load the lib
```bash
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
. "$HERE/../lib.sh"
```

## b. goto exo dir
```bash
enter_exercise <module> <exo>
```

## c. set variables
set `NAME` and `SRCS` (also `HEADERS` if it has '.hpp' files) variables

## d. do standard checks:
```bash
check_file_exist Makefile $SRCS
check_makefile main.cpp
check_norm $SRCS
```

## e. never use following methods
- `summary`
- `exit`

## f. naming convetions
The script must be called `exNN.sh` and located in `tests/<module>/`.

## g. running the script
```bash
./tests/run.sh        # all tests
./tests/run.sh 00     # all tests for module 00
./tests/run.sh 00 01  # only testing ex01 from module 00
```

