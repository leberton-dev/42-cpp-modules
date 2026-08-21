CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Zombie.cpp newZombie.cpp randomChump.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := Zombie.hpp

NAME := zomb

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
	@../test/ex00.sh

.PHONY: all clean fclean re
