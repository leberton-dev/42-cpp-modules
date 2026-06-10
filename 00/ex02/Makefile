SHELL := /bin/bash
NAME = account
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = Account.cpp tests.cpp

OBJS = $(SRCS:.cpp=.o)

HEADERS = Account.hpp

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	@../test/ex02.sh

.PHONY: all clean fclean re
