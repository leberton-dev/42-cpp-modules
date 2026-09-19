CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Animal.cpp Dog.cpp Cat.cpp WrongAnimal.cpp WrongCat.cpp
OBJS := $(SRCS:.cpp=.o)
HEAD := Animal.hpp Dog.hpp Cat.hpp WrongAnimal.hpp WrongCat.hpp

NAME := polymorphism

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
