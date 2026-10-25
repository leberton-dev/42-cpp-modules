.PHONY: all clean fclean re

all: prog

prog: build/main.o
	c++ -Wall -Wextra -Werror -std=c++98 $^ -o $@

build/%.o: %.cpp whatever.hpp | build
	c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

build:
	@mkdir -p build

clean:
	rm -rf build

fclean: clean
	rm -f prog

re: fclean all
