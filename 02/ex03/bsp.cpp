#include "Point.hpp"

static long side(Point const &a, Point const &b, Point const &p) {
  long ax = a.getX().getRawBits();
  long ay = a.getY().getRawBits();
  long bx = b.getX().getRawBits();
  long by = b.getY().getRawBits();
  long px = p.getX().getRawBits();
  long py = p.getY().getRawBits();

  return (bx - ax) * (py - ay) - (by - ay) * (px - ax);
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
  long d1 = side(a, b, point);
  long d2 = side(b, c, point);
  long d3 = side(c, a, point);

  return (d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0);
}
