NAME := phonebook
CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Contact.cpp PhoneBook.cpp Program.cpp

OBJS := $(SRCS:.cpp=.o)

HEADERS := Contact.hpp PhoneBook.hpp Program.hpp

TEST_DIR := tests
TEST_INPUT := $(TEST_DIR)/input
TEST_CAUGHT := $(TEST_DIR)/caught
TEST_EXPECTED := $(TEST_DIR)/expected
TEST_INPUTS := $(wildcard $(TEST_INPUT)/*.input)

RM := rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r "$(TEST_DIR)/caught"

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	@../test/ex01.sh

.PHONY: all clean fclean re test
