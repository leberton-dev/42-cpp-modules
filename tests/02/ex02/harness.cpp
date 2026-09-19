#include "Fixed.hpp"
#include "check.hpp"
#include <climits>
#include <sstream>

static Fixed raw(int r) { Fixed f; f.setRawBits(r); return f; }
static int R(const Fixed &f) { return f.getRawBits(); }
static std::string str(const Fixed &f) { std::ostringstream o; o << f; return o.str(); }

static unsigned long seed = 12345;
static long rnd(long lo, long hi) { // deterministic LCG
	seed = seed * 1103515245UL + 12345UL;
	return lo + (long)((seed >> 8) % (unsigned long)(hi - lo + 1));
}

static bool near(long a, long b, long tol) { return (a > b ? a - b : b - a) <= tol; }

int main() {
	// ---------- comparisons ----------
	{
		int vals[] = {-512, -256, -1, 0, 1, 255, 256, 257, 100000};
		bool okLt = true, okGt = true, okLe = true, okGe = true, okEq = true, okNe = true;
		for (unsigned i = 0; i < sizeof(vals) / sizeof(*vals); i++)
			for (unsigned j = 0; j < sizeof(vals) / sizeof(*vals); j++) {
				Fixed a = raw(vals[i]), b = raw(vals[j]);
				okLt = okLt && ((a < b) == (vals[i] < vals[j]));
				okGt = okGt && ((a > b) == (vals[i] > vals[j]));
				okLe = okLe && ((a <= b) == (vals[i] <= vals[j]));
				okGe = okGe && ((a >= b) == (vals[i] >= vals[j]));
				okEq = okEq && ((a == b) == (vals[i] == vals[j]));
				okNe = okNe && ((a != b) == (vals[i] != vals[j]));
			}
		CHECK("operator<  (81 pairs incl. negatives)", okLt);
		CHECK("operator>  (81 pairs incl. negatives)", okGt);
		CHECK("operator<= (81 pairs incl. negatives)", okLe);
		CHECK("operator>= (81 pairs incl. negatives)", okGe);
		CHECK("operator== (81 pairs incl. negatives)", okEq);
		CHECK("operator!= (81 pairs incl. negatives)", okNe);
		CHECK("Fixed(1) == Fixed(1.0f)", Fixed(1) == Fixed(1.0f));
		CHECK("Fixed(0.1f) != Fixed(0.2f)", Fixed(0.1f) != Fixed(0.2f));
		CHECK("comparison returns bool 1/0", (Fixed(1) < Fixed(2)) == true && (Fixed(2) < Fixed(1)) == false);
	}
	// ---------- arithmetic: exactly representable cases ----------
	{
		CHECK("1.5 + 2.25 == 3.75", R(Fixed(1.5f) + Fixed(2.25f)) == R(Fixed(3.75f)));
		CHECK("1 + -3 == -2", R(Fixed(1) + Fixed(-3)) == R(Fixed(-2)));
		CHECK("5 - 7.5 == -2.5", R(Fixed(5) - Fixed(7.5f)) == R(Fixed(-2.5f)));
		CHECK("0 - 0 == 0", R(Fixed() - Fixed()) == 0);
		CHECK("3 * 4 == 12", R(Fixed(3) * Fixed(4)) == R(Fixed(12)));
		CHECK("0.5 * 0.5 == 0.25", R(Fixed(0.5f) * Fixed(0.5f)) == R(Fixed(0.25f)));
		CHECK("-2 * 3.5 == -7", R(Fixed(-2) * Fixed(3.5f)) == R(Fixed(-7)));
		CHECK("-2 * -3 == 6", R(Fixed(-2) * Fixed(-3)) == R(Fixed(6)));
		CHECK("1.5 * 1.5 == 2.25", R(Fixed(1.5f) * Fixed(1.5f)) == R(Fixed(2.25f)));
		CHECK("x * 0 == 0", R(Fixed(123.5f) * Fixed(0)) == 0);
		CHECK("x * 1 == x", R(Fixed(123.5f) * Fixed(1)) == R(Fixed(123.5f)));
		CHECK("subject: 5.05f * 2 raw == 2586 (10.1016)", R(Fixed(5.05f) * Fixed(2)) == 2586);
		CHECK("10 / 4 == 2.5", R(Fixed(10) / Fixed(4)) == R(Fixed(2.5f)));
		CHECK("-9 / 3 == -3", R(Fixed(-9) / Fixed(3)) == R(Fixed(-3)));
		CHECK("9 / -3 == -3", R(Fixed(9) / Fixed(-3)) == R(Fixed(-3)));
		CHECK("-9 / -3 == 3", R(Fixed(-9) / Fixed(-3)) == R(Fixed(3)));
		CHECK("1 / 2 == 0.5", R(Fixed(1) / Fixed(2)) == R(Fixed(0.5f)));
		CHECK("x / 1 == x", R(Fixed(77.25f) / Fixed(1)) == R(Fixed(77.25f)));
		CHECK("0 / x == 0", R(Fixed(0) / Fixed(9)) == 0);
		CHECK("1 / 3 ~= 85 or 86 raw", near(R(Fixed(1) / Fixed(3)), 85, 1));
		CHECK("-1 / 3 ~= -85 or -86 raw", near(R(Fixed(-1) / Fixed(3)), -85, 1));
		CHECK("smallest * 1 keeps epsilon", R(raw(1) * Fixed(1)) == 1);
		CHECK("(a+b)*c-d/e chain == 10", R((Fixed(1) + Fixed(2)) * Fixed(4) - Fixed(4) / Fixed(2)) == R(Fixed(10)));
		{
			Fixed a(2), b(3);
			Fixed c = a * b + a - b;
			CHECK("operators return new values (operands untouched)", R(a) == R(Fixed(2)) && R(b) == R(Fixed(3)) && R(c) == R(Fixed(5)));
		}
		CHECK("division by zero does not hang/crash the process", (Fixed(1) / Fixed(0), true));
	}
	// ---------- arithmetic: fuzz against integer reference ----------
	{
		int badAdd = 0, badSub = 0, badMul = 0, badDiv = 0, badCmp = 0;
		for (int i = 0; i < 20000; i++) {
			long a = rnd(-30000, 30000), b = rnd(-30000, 30000);
			Fixed fa = raw((int)a), fb = raw((int)b);
			if (R(fa + fb) != (int)(a + b)) badAdd++;
			if (R(fa - fb) != (int)(a - b)) badSub++;
			if (!near(R(fa * fb), (a * b) / 256, 1)) badMul++;
			if (b != 0 && !near(R(fa / fb), (a * 256) / b, 1)) badDiv++;
			if ((fa < fb) != (a < b) || (fa >= fb) != (a >= b)) badCmp++;
		}
		std::ostringstream d;
		d << badAdd << " wrong"; chk::report(badAdd == 0, "fuzz 20000: + exact", d.str()); d.str("");
		d << badSub << " wrong"; chk::report(badSub == 0, "fuzz 20000: - exact", d.str()); d.str("");
		d << badMul << " wrong"; chk::report(badMul == 0, "fuzz 20000: * within 1 epsilon of (a*b)>>8", d.str()); d.str("");
		d << badDiv << " wrong"; chk::report(badDiv == 0, "fuzz 20000: / within 1 epsilon of (a<<8)/b", d.str()); d.str("");
		d << badCmp << " wrong"; chk::report(badCmp == 0, "fuzz 20000: comparisons", d.str());
	}
	// ---------- 32-bit overflow safety of * and / (intermediate must not wrap) ----------
	{
		CHECK("100 * 100 == 10000 (raw product 6.5e8 fits int)", R(Fixed(100) * Fixed(100)) == R(Fixed(10000)));
		CHECK("2000 * 2000 == 4e6 (raw product 2.6e11 overflows int32 but must not)", R(Fixed(2000) * Fixed(2000)) == R(Fixed(4000000)));
		CHECK("4000 / 0.5 == 8000 (numerator << 8 overflows int32 but must not)", R(Fixed(4000) / Fixed(0.5f)) == R(Fixed(8000)));
	}
	// ---------- increment / decrement ----------
	{
		Fixed a;
		CHECK("++0 == 0.00390625 (raw 1)", R(++a) == 1);
		CHECK("value after pre-inc", R(a) == 1);
		CHECK("pre-inc returns the object itself", &(++a) == &a);
		CHECK("a is now raw 2", R(a) == 2);
		Fixed old = a++;
		CHECK("post-inc returns old value", R(old) == 2);
		CHECK("post-inc incremented the object", R(a) == 3);
		CHECK("post-inc returns a copy, not a reference", &old != &a);
		CHECK("pre-dec returns the object itself", &(--a) == &a);
		CHECK("value after pre-dec", R(a) == 2);
		Fixed old2 = a--;
		CHECK("post-dec returns old value", R(old2) == 2);
		CHECK("post-dec decremented the object", R(a) == 1);
		Fixed z;
		--z;
		CHECK("--0 == -0.00390625 (raw -1)", R(z) == -1);
		Fixed one(1);
		CHECK("epsilon: 1 + eps > 1", raw(R(one) + 1) > one);
		CHECK("epsilon: ++ is the SMALLEST step (no value strictly between)", R(++Fixed(one)) == R(one) + 1);
		CHECK("eps == 1/256 via output", str(raw(1)) == "0.00390625");
		std::ostringstream o;
		Fixed p;
		o << p << " " << ++p << " " << p << " " << p++ << " " << p;
		CHECK("subject sequence 0 / 0.0039 / 0.0039 / 0.0039 / 0.0078",
			o.str() == "0 0.00390625 0.00390625 0.00390625 0.0078125");
	}
	// ---------- min / max ----------
	{
		Fixed a(1), b(2);
		const Fixed ca(1), cb(2);
		CHECK("min(non-const) returns reference to smaller", &Fixed::min(a, b) == &a);
		CHECK("max(non-const) returns reference to greater", &Fixed::max(a, b) == &b);
		CHECK("min(non-const) symmetrical args", &Fixed::min(b, a) == &a);
		CHECK("max(non-const) symmetrical args", &Fixed::max(b, a) == &b);
		CHECK("min(const) returns reference to smaller", &Fixed::min(ca, cb) == &ca);
		CHECK("max(const) returns reference to greater", &Fixed::max(ca, cb) == &cb);
		Fixed::min(a, b) = Fixed(9);
		CHECK("non-const min result is writable (real reference)", R(a) == R(Fixed(9)));
		Fixed n1(-5), n2(-2);
		CHECK("min with negatives", &Fixed::min(n1, n2) == &n1);
		CHECK("max with negatives", &Fixed::max(n1, n2) == &n2);
		Fixed e1(3), e2(3);
		Fixed &m = Fixed::min(e1, e2);
		CHECK("min of equal values returns one of the two", &m == &e1 || &m == &e2);
		CHECK("min/max accept temporaries (const overload)", R(Fixed::max(Fixed(1), Fixed(2))) == R(Fixed(2)) && R(Fixed::min(Fixed(1), Fixed(2))) == R(Fixed(1)));
		CHECK("min/max on raw-1 difference", R(Fixed::max(raw(1), raw(2))) == 2 && R(Fixed::min(raw(1), raw(2))) == 1);
		CHECK("subject max(a,b): a=0.0078125 b=10.1016 -> 10.1016",
			str(Fixed::max(raw(2), Fixed(5.05f) * Fixed(2))) == "10.1016");
	}
	// ---------- const correctness / copy ----------
	{
		const Fixed x(4), y(2);
		CHECK("const objects: all binary ops compile & work",
			R(x + y) == R(Fixed(6)) && R(x - y) == R(Fixed(2)) && R(x * y) == R(Fixed(8)) && R(x / y) == R(Fixed(2))
			&& (x > y) && (y < x) && (x >= y) && (y <= x) && (x != y) && !(x == y));
		Fixed a(3), b, c;
		c = b = a;
		CHECK("chained assignment", R(b) == R(a) && R(c) == R(a));
		Fixed &s = a; a = s;
		CHECK("self assignment", R(a) == R(Fixed(3)));
		Fixed d(a);
		CHECK("copy ctor", R(d) == R(a));
	}
	return 0;
}
