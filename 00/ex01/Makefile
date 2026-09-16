NAME := phonebook
CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Contact.cpp PhoneBook.cpp Program.cpp

OBJS := $(SRCS:.cpp=.o)

HEADERS := Contact.hpp PhoneBook.hpp Program.hpp

RM := rm -f

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


.PHONY: all clean fclean re
