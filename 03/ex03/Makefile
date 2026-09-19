CC := c++
CFLAGS := -Wall -Wextra -Werror -Wshadow -std=c++98

SRCS := main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := ClapTrap.hpp ScavTrap.hpp FragTrap.hpp DiamondTrap.hpp

NAME := diamondTrap

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
