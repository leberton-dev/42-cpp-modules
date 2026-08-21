CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)

NAME := hit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@../test/ex02.sh

.PHONY: all clean fclean re
