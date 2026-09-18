CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Fixed.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := Fixed.hpp

NAME := fixed

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

.PHONY: all clean fclean re
