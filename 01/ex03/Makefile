CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Weapon.cpp HumanA.cpp HumanB.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := Weapon.hpp HumanA.hpp HumanB.hpp

NAME := violence

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
	@../test/ex03.sh

.PHONY: all clean fclean re test
