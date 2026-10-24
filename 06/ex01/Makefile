.PHONY: all clean fclean re build

OBJS	:= build/main.o build/Serializer.o

all: prog

prog: $(OBJS) Serializer.hpp
	c++ -Wall -Wextra -Werror -std=c++98 $^ -o prog

build/%.o: %.cpp Serializer.hpp | build
	c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

fclean: clean
	rm -f prog

re: fclean all
