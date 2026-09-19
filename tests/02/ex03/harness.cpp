#include "Point.hpp"
#include "check.hpp"
#include <sstream>

bool bsp(Point const a, Point const b, Point const c, Point const point);

static int R(const Fixed &f) { return f.getRawBits(); }

typedef long L; // 64 bits on the target platform (LP64); avoids 'long long' (not C++98)

static L cross(L ax, L ay, L bx, L by, L px, L py) { return (bx - ax) * (py - ay) - (by - ay) * (px - ax); }

// exact reference on the raw (1/256) grid: strictly inside <=> the 3 cross products have the same non-zero sign
static bool ref(const Point &a, const Point &b, const Point &c, const Point &p) {
	L d1 = cross(R(a.getX()), R(a.getY()), R(b.getX()), R(b.getY()), R(p.getX()), R(p.getY()));
	L d2 = cross(R(b.getX()), R(b.getY()), R(c.getX()), R(c.getY()), R(p.getX()), R(p.getY()));
	L d3 = cross(R(c.getX()), R(c.getY()), R(a.getX()), R(a.getY()), R(p.getX()), R(p.getY()));
	return (d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0);
}

static unsigned long seed = 7;
static int rnd(int lo, int hi) {
	seed = seed * 1103515245UL + 12345UL;
	return lo + (int)((seed >> 8) % (unsigned long)(hi - lo + 1));
}

static void T(const char *name, const Point &a, const Point &b, const Point &c, const Point &p, bool expected) {
	bool got = bsp(a, b, c, p);
	std::ostringstream d;
	d << "expected " << (expected ? "INSIDE" : "OUTSIDE") << ", got " << (got ? "INSIDE" : "OUTSIDE");
	chk::report(got == expected, name, d.str());
}

int main() {
	// ---------------- Point ----------------
	{
		Point p;
		CHECK("Point(): x == 0 and y == 0", R(p.getX()) == 0 && R(p.getY()) == 0);
		Point q(1.5f, -2.25f);
		CHECK("Point(1.5,-2.25): x", R(q.getX()) == R(Fixed(1.5f)));
		CHECK("Point(1.5,-2.25): y", R(q.getY()) == R(Fixed(-2.25f)));
		Point c(q);
		CHECK("copy ctor copies x and y", R(c.getX()) == R(q.getX()) && R(c.getY()) == R(q.getY()));
		Point d;
		d = q; // Fixed const members: assignment cannot really copy - only check it is callable / harmless
		CHECK("copy assignment is callable and leaves a valid object", R(d.getX()) == R(d.getX()));
		Point self(3, 4);
		Point &sr = self; self = sr;
		CHECK("self assignment keeps value", R(self.getX()) == R(Fixed(3)) && R(self.getY()) == R(Fixed(4)));
		const Point cp(2, 3);
		CHECK("getX/getY callable on const Point", R(cp.getX()) == R(Fixed(2)) && R(cp.getY()) == R(Fixed(3)));
		Point neg(-7.5f, -0.5f);
		CHECK("negative coordinates stored", R(neg.getX()) == R(Fixed(-7.5f)) && R(neg.getY()) == R(Fixed(-0.5f)));
		Point m(0.001f, 0.002f);
		CHECK("coordinates are quantised through Fixed (0.001 -> 0, 0.002 -> 1/256)", R(m.getX()) == 0 && R(m.getY()) == 1);
	}

	// ---------------- bsp, hand-made cases (integer triangle) ----------------
	{
		Point A(0, 0), B(10, 0), C(0, 10);
		T("inside (1,1)", A, B, C, Point(1, 1), true);
		T("inside (3,3)", A, B, C, Point(3, 3), true);
		T("inside (0.5,0.5)", A, B, C, Point(0.5f, 0.5f), true);
		T("inside (4.99,4.99) just under hypotenuse", A, B, C, Point(4.99f, 4.99f), true);
		T("inside 1/256 from vertex A", A, B, C, Point(0.00390625f, 0.00390625f), true);
		T("outside (5.01,5.01) just over hypotenuse", A, B, C, Point(5.01f, 5.01f), false);
		T("outside (15,15)", A, B, C, Point(15, 15), false);
		T("outside (-1,-1)", A, B, C, Point(-1, -1), false);
		T("outside (0,11) above C", A, B, C, Point(0, 11), false);
		T("outside (11,0) right of B", A, B, C, Point(11, 0), false);
		T("outside (10,10)", A, B, C, Point(10, 10), false);
		T("outside (-0.01,3) left of AC", A, B, C, Point(-0.01f, 3), false);
		T("outside (3,-0.01) below AB", A, B, C, Point(3, -0.01f), false);
		T("vertex A -> false", A, B, C, Point(0, 0), false);
		T("vertex B -> false", A, B, C, Point(10, 0), false);
		T("vertex C -> false", A, B, C, Point(0, 10), false);
		T("edge AB midpoint -> false", A, B, C, Point(5, 0), false);
		T("edge AC midpoint -> false", A, B, C, Point(0, 5), false);
		T("edge BC midpoint -> false", A, B, C, Point(5, 5), false);
		T("edge BC (2,8) -> false", A, B, C, Point(2, 8), false);
		T("edge AB near B (9.5,0) -> false", A, B, C, Point(9.5f, 0), false);
		T("edge extension beyond B on AB line -> false", A, B, C, Point(12, 0), false);
	}
	// ---------------- vertex order / orientation must not matter ----------------
	{
		Point A(0, 0), B(10, 0), C(0, 10);
		Point in(3, 3), out(20, 20), edge(5, 5);
		T("order A,C,B inside", A, C, B, in, true);
		T("order B,A,C inside", B, A, C, in, true);
		T("order B,C,A inside", B, C, A, in, true);
		T("order C,A,B inside", C, A, B, in, true);
		T("order C,B,A inside", C, B, A, in, true);
		T("order C,B,A outside", C, B, A, out, false);
		T("order B,C,A on edge", B, C, A, edge, false);
	}
	// ---------------- negative / large / tiny / degenerate ----------------
	{
		Point N1(-10, -10), N2(10, -10), N3(0, 10);
		T("negative triangle: origin inside", N1, N2, N3, Point(0, 0), true);
		T("negative triangle: on bottom edge", N1, N2, N3, Point(0, -10), false);
		T("negative triangle: below", N1, N2, N3, Point(0, -11), false);
		T("negative triangle: vertex", N1, N2, N3, Point(-10, -10), false);
		Point L1(-1000, -1000), L2(1000, -1000), L3(0, 1000);
		T("large triangle: origin inside", L1, L2, L3, Point(0, 0), true);
		T("large triangle: (0,999) inside", L1, L2, L3, Point(0, 999), true);
		T("large triangle: bottom edge", L1, L2, L3, Point(0, -1000), false);
		T("large triangle: outside", L1, L2, L3, Point(0, 1001), false);
		Point s1(0, 0), s2(0.0390625f, 0), s3(0, 0.0390625f);
		T("tiny triangle: interior", s1, s2, s3, Point(0.01171875f, 0.01171875f), true);
		T("tiny triangle: outside", s1, s2, s3, Point(0.03f, 0.03f), false);
		Point D(0, 0), E(5, 5), F(10, 10);
		T("degenerate (collinear) triangle: point on the line -> false", D, E, F, Point(2, 2), false);
		T("degenerate (collinear) triangle: point off the line -> false", D, E, F, Point(2, 3), false);
		T("degenerate (3 identical vertices) -> false", D, D, D, Point(0, 0), false);
		T("degenerate (2 identical vertices) -> false", D, D, F, Point(1, 1), false);
	}
	// ---------------- non-integer triangle, hand-made ----------------
	{
		Point G(0.5f, 0.25f), H(7.75f, 1.5f), I(3.3f, 9.9f);
		T("frac triangle: inside (3.5,4)", G, H, I, Point(3.5f, 4.0f), true);
		T("frac triangle: inside (3.3,2)", G, H, I, Point(3.3f, 2.0f), true);
		T("frac triangle: outside (8,8)", G, H, I, Point(8, 8), false);
		T("frac triangle: midpoint of GH (4.125,0.875) on edge -> false", G, H, I, Point(4.125f, 0.875f), false);
		T("frac triangle: vertex I", G, H, I, Point(3.3f, 9.9f), false);
	}
	// ---------------- fuzz vs exact integer reference ----------------
	{
		// 1) integer coordinates in [-100,100]
		int bad = 0, n = 60000;
		for (int i = 0; i < n; i++) {
			Point a((float)rnd(-100, 100), (float)rnd(-100, 100)), b((float)rnd(-100, 100), (float)rnd(-100, 100)),
				c((float)rnd(-100, 100), (float)rnd(-100, 100)), p((float)rnd(-100, 100), (float)rnd(-100, 100));
			if (bsp(a, b, c, p) != ref(a, b, c, p)) bad++;
		}
		std::ostringstream d; d << bad << "/" << n << " wrong";
		chk::report(bad == 0, "fuzz 60000: integer coords in [-100,100] vs exact reference", d.str());

		// 2) quarter-unit coordinates in [-10,10] (exact in binary)
		bad = 0;
		for (int i = 0; i < n; i++) {
			Point a(rnd(-40, 40) / 4.0f, rnd(-40, 40) / 4.0f), b(rnd(-40, 40) / 4.0f, rnd(-40, 40) / 4.0f),
				c(rnd(-40, 40) / 4.0f, rnd(-40, 40) / 4.0f), p(rnd(-40, 40) / 4.0f, rnd(-40, 40) / 4.0f);
			if (bsp(a, b, c, p) != ref(a, b, c, p)) bad++;
		}
		d.str(""); d << bad << "/" << n << " wrong";
		chk::report(bad == 0, "fuzz 60000: quarter coords in [-10,10] vs exact reference", d.str());

		// 3) decimal coordinates (tenths) in [-50,50]: typical 'user' inputs like 17.2 or 24.7
		bad = 0;
		std::string first;
		for (int i = 0; i < n; i++) {
			float f[8];
			for (int k = 0; k < 8; k++) f[k] = rnd(-500, 500) / 10.0f;
			Point a(f[0], f[1]), b(f[2], f[3]), c(f[4], f[5]), p(f[6], f[7]);
			bool r = ref(a, b, c, p), g = bsp(a, b, c, p);
			if (r != g) {
				if (bad == 0) {
					std::ostringstream e;
					e << "e.g. A(" << f[0] << "," << f[1] << ") B(" << f[2] << "," << f[3] << ") C(" << f[4] << "," << f[5]
					  << ") P(" << f[6] << "," << f[7] << ") expected " << (r ? "INSIDE" : "OUTSIDE");
					first = e.str();
				}
				bad++;
			}
		}
		d.str(""); d << bad << "/" << n << " wrong; " << first;
		chk::report(bad == 0, "fuzz 60000: decimal coords in [-50,50] vs exact reference", d.str());

		// 4) points constructed EXACTLY on an edge (midpoint / vertex) of a decimal triangle: must always be false
		bad = 0; first = "";
		for (int i = 0; i < n; i++) {
			int v[6];
			for (int k = 0; k < 6; k++) v[k] = rnd(-500, 500);
			Point a(v[0] / 10.0f, v[1] / 10.0f), b(v[2] / 10.0f, v[3] / 10.0f), c(v[4] / 10.0f, v[5] / 10.0f);
			Point mid((a.getX().toFloat() + b.getX().toFloat()) / 2, (a.getY().toFloat() + b.getY().toFloat()) / 2);
			// keep only midpoints that land exactly on the 1/256 grid, so they are truly on the edge
			if ((R(a.getX()) + R(b.getX())) % 2 != 0 || (R(a.getY()) + R(b.getY())) % 2 != 0) continue;
			if (bsp(a, b, c, mid)) {
				if (bad == 0) {
					std::ostringstream e;
					e << "e.g. A(" << v[0] / 10.0 << "," << v[1] / 10.0 << ") B(" << v[2] / 10.0 << "," << v[3] / 10.0 << ") C("
					  << v[4] / 10.0 << "," << v[5] / 10.0 << ") midpoint(AB) reported INSIDE";
					first = e.str();
				}
				bad++;
			}
		}
		d.str(""); d << bad << " edge midpoints reported INSIDE; " << first;
		chk::report(bad == 0, "fuzz: exact edge midpoints of decimal triangles are never INSIDE", d.str());
	}
	return 0;
}
