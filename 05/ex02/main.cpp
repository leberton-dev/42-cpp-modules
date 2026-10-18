#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void) {
	Bureaucrat b("Bob", 1);
	ShrubberyCreationForm s("test");
	b.signForm(s);

	s.execute(b);
}
