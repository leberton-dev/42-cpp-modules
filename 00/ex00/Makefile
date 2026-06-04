NAME =		megaphone
CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98
SRCS =		megaphone.cpp

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

test: all
	@./test.sh

.PHONY: all clean fclean re test
