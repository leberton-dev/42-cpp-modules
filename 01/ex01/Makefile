CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Zombie.cpp zombieHorde.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := Zombie.hpp

NAME := zombieHorde

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
	@../test/ex01.sh

.PHONY: all clean fclean re
