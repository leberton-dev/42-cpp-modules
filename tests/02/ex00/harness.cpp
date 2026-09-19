#include "Fixed.hpp"
#include "check.hpp"
#include <climits>

int main() {
	{ Fixed a; CHECK("default raw == 0", a.getRawBits() == 0); }
	{
		Fixed a;
		a.setRawBits(42);   CHECK("set/get 42", a.getRawBits() == 42);
		a.setRawBits(-42);  CHECK("set/get -42", a.getRawBits() == -42);
		a.setRawBits(INT_MAX); CHECK("set/get INT_MAX", a.getRawBits() == INT_MAX);
		a.setRawBits(INT_MIN); CHECK("set/get INT_MIN", a.getRawBits() == INT_MIN);
	}
	{
		Fixed a; a.setRawBits(1234);
		Fixed b(a);
		CHECK("copy ctor copies value", b.getRawBits() == 1234);
		b.setRawBits(1); CHECK("copy is independent (source unchanged)", a.getRawBits() == 1234);
		a.setRawBits(2); CHECK("copy is independent (copy unchanged)", b.getRawBits() == 1);
	}
	{
		Fixed a, b, c; a.setRawBits(77);
		c = b = a;
		CHECK("assignment copies value", b.getRawBits() == 77);
		CHECK("chained assignment a=b=c", c.getRawBits() == 77);
		Fixed &r = (b = a);
		CHECK("operator= returns *this", &r == &b);
		Fixed &self = a;
		a = self;
		CHECK("self assignment keeps value", a.getRawBits() == 77);
	}
	{
		Fixed a; a.setRawBits(5);
		const Fixed c(a);
		CHECK("getRawBits callable on const object", c.getRawBits() == 5);
	}
	// messages
	{
		chk::Capture c;
		{ Fixed a; }
		std::string o = c.stop();
		CHECK("default ctor + dtor messages, each on its own line",
			o == "Default constructor called\nDestructor called\n");
	}
	{
		Fixed a;
		chk::Capture c;
		{ Fixed b(a); }
		std::string o = c.stop();
		CHECK("copy ctor message then dtor", chk::inOrder(o, "Copy constructor called", "Destructor called"));
		CHECK("every message ends with newline", !o.empty() && o[o.size() - 1] == '\n');
	}
	{
		Fixed a, b;
		chk::Capture c;
		b = a;
		std::string o = c.stop();
		CHECK("assignment prints 'Copy assignment operator called'", chk::has(o, "Copy assignment operator called\n"));
	}
	{
		Fixed a;
		chk::Capture c;
		a.getRawBits();
		std::string o = c.stop();
		CHECK("getRawBits prints its message", o == "getRawBits member function called\n");
	}
	return 0;
}
