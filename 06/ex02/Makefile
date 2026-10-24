.PHONY: all clean fclean re build

OBJS	:= build/main.o build/Base.o build/A.o build/B.o build/C.o
HEADERS	:= Base.hpp A.hpp B.hpp C.hpp

all: prog

prog: $(OBJS)
	c++ -Wall -Wextra -Werror -std=c++98 $^ -o prog

build/%.o: %.cpp $(HEADERS) | build
	c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

build:
	@mkdir -p build

clean:
	rm -rf build

fclean: clean
	rm -f prog

re: fclean all
