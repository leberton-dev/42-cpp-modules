.PHONY: all clean fclean re

CFLAGS	:= -Wall -Wextra -Werror -std=c++98

SOURCES	:= AForm.cpp Bureaucrat.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp main.cpp
HEADERS	:= AForm.hpp Bureaucrat.hpp ShrubberyCreationForm.hpp RobotomyRequestForm.hpp PresidentialPardonForm.hpp Intern.hpp
BUILD	:= build
OBJECTS	:= $(SOURCES:%.cpp=$(BUILD)/%.o)

NAME	:= prog

all: $(NAME)

$(NAME): $(OBJECTS)
	c++ $(CFLAGS) -o $@ $(OBJECTS)

$(BUILD)/%.o: %.cpp $(HEADERS) | $(BUILD)
	c++ $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all
