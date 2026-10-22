.PHONY: all clean fclean re

HEADERS		:= ScalarConverter.hpp
OBJECTS		:= build/ScalarConverter.o build/main.o

all: convert

convert: $(OBJECTS)
	c++ -Wall -Wextra -Werror -std=c++98 $^ -o $@

build/%.o: %.cpp $(HEADERS) | build
	c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

fclean: clean
	rm -f convert

re: fclean all
