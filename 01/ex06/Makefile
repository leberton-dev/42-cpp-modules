CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp main.cpp Harl.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := Harl.hpp

NAME := harlFilter

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.cpp $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@../test/ex06.sh

.PHONY: all clean fclean re
