#include "Fixed.hpp"
#include "check.hpp"
#include <climits>
#include <sstream>

static std::string str(const Fixed &f) { std::ostringstream o; o << f; return o.str(); }

int main() {
	// --- int constructor
	{
		int v[] = {0, 1, -1, 2, 42, -42, 1000, -1000, 8388607, -8388608};
		for (unsigned i = 0; i < sizeof(v) / sizeof(*v); i++) {
			std::ostringstream n; n << "Fixed(" << v[i] << ").raw == " << v[i] << "*256";
			Fixed f(v[i]);
			CHECK(n.str(), f.getRawBits() == v[i] * 256);
		}
		bool ok = true;
		for (int i = -3000; i <= 3000; i++) ok = ok && (Fixed(i).toInt() == i) && (Fixed(i).toFloat() == (float)i);
		CHECK("int -> Fixed -> toInt / toFloat round-trip on [-3000,3000]", ok);
	}
	// --- float constructor (round to nearest, 8 fractional bits)
	{
		CHECK("Fixed(0.0f) raw 0", Fixed(0.0f).getRawBits() == 0);
		CHECK("Fixed(1.0f) raw 256", Fixed(1.0f).getRawBits() == 256);
		CHECK("Fixed(-1.5f) raw -384", Fixed(-1.5f).getRawBits() == -384);
		CHECK("Fixed(42.42f) raw 10860 (rounded, not truncated)", Fixed(42.42f).getRawBits() == 10860);
		CHECK("Fixed(1234.4321f) raw 316015", Fixed(1234.4321f).getRawBits() == 316015);
		CHECK("Fixed(0.1f) raw 26 (25.6 rounded up)", Fixed(0.1f).getRawBits() == 26);
		CHECK("Fixed(0.001f) raw 0 (0.256 rounded down)", Fixed(0.001f).getRawBits() == 0);
		CHECK("Fixed(0.002f) raw 1 (0.512 rounded up)", Fixed(0.002f).getRawBits() == 1);
		CHECK("Fixed(-0.002f) raw -1", Fixed(-0.002f).getRawBits() == -1);
		CHECK("Fixed(1/512.f) half rounds away from zero -> 1", Fixed(1.0f / 512).getRawBits() == 1);
		CHECK("Fixed(-1/512.f) half rounds away from zero -> -1", Fixed(-1.0f / 512).getRawBits() == -1);
		bool ok = true;
		for (int r = -4000; r <= 4000; r++) ok = ok && (Fixed(r / 256.0f).getRawBits() == r);
		CHECK("every raw in [-4000,4000] survives float round-trip", ok);
	}
	// --- toFloat / toInt
	{
		Fixed f; f.setRawBits(1);
		CHECK("toFloat(raw 1) == 1/256 exactly", f.toFloat() == 0.00390625f);
		f.setRawBits(-1);
		CHECK("toFloat(raw -1) == -1/256", f.toFloat() == -0.00390625f);
		CHECK("toInt(42.99) == 42", Fixed(42.99f).toInt() == 42);
		CHECK("toInt(42.42f) == 42", Fixed(42.42f).toInt() == 42);
		CHECK("toInt(0.99) == 0", Fixed(0.99f).toInt() == 0);
		CHECK("toInt(-3) == -3", Fixed(-3).toInt() == -3);
		const Fixed c(3.5f);
		CHECK("toFloat/toInt callable on const", c.toFloat() == 3.5f && c.toInt() == 3);
	}
	// --- operator<<
	{
		CHECK("<< 0", str(Fixed()) == "0");
		CHECK("<< 10", str(Fixed(10)) == "10");
		CHECK("<< 42.4219", str(Fixed(42.42f)) == "42.4219");
		CHECK("<< 1234.43", str(Fixed(1234.4321f)) == "1234.43");
		CHECK("<< -1.5", str(Fixed(-1.5f)) == "-1.5");
		CHECK("<< -3", str(Fixed(-3)) == "-3");
		Fixed f; f.setRawBits(1);
		CHECK("<< 0.00390625", str(f) == "0.00390625");
		std::ostringstream o;
		o << Fixed(1) << "|" << Fixed(2);
		CHECK("<< is chainable and returns the stream", o.str() == "1|2");
		std::ostream &r = (o << Fixed(3));
		CHECK("<< returns the same stream reference", &r == &o);
	}
	// --- constructors / copy
	{
		Fixed a(7.5f), b(a), c;
		c = a;
		CHECK("copy ctor keeps value", b.getRawBits() == a.getRawBits());
		CHECK("assignment keeps value", c.getRawBits() == a.getRawBits());
		Fixed d = Fixed(3);
		CHECK("copy-init from int ctor", d.getRawBits() == 768);
		CHECK("ambiguity: Fixed(5) is int ctor, Fixed(5.0f) is float ctor",
			Fixed(5).getRawBits() == Fixed(5.0f).getRawBits());
	}
	// --- messages
	{
		chk::Capture c; { Fixed a(3); } std::string o = c.stop();
		CHECK("int ctor message", o == "Int constructor called\nDestructor called\n");
	}
	{
		chk::Capture c; { Fixed a(3.0f); } std::string o = c.stop();
		CHECK("float ctor message", o == "Float constructor called\nDestructor called\n");
	}
	{
		chk::Capture c; { Fixed a; } std::string o = c.stop();
		CHECK("default ctor message", o == "Default constructor called\nDestructor called\n");
	}
	{
		Fixed a; chk::Capture c; { Fixed b(a); } std::string o = c.stop();
		CHECK("copy ctor message", chk::has(o, "Copy constructor called\n"));
	}
	return 0;
}
