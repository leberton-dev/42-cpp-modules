#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point);

void runTest(Point a, Point b, Point c, Point p, const std::string &desc) {
  std::cout << desc << " -> ";
  if (bsp(a, b, c, p))
    std::cout << "INSIDE" << std::endl;
  else
    std::cout << "OUTSIDE" << std::endl;
}

int main(void) {
  Point a(0, 0);
  Point b(10, 0);
  Point c(0, 10);

  // Inside
  runTest(a, b, c, Point(1, 1), "( 1,  1) - near corner A");
  runTest(a, b, c, Point(2, 2), "( 2,  2) - lower center");
  runTest(a, b, c, Point(3, 3), "( 3,  3) - middle");

  std::cout << std::endl;
  // Outside
  runTest(a, b, c, Point(15, 15), "(15, 15) - far along the diagonal");
  runTest(a, b, c, Point(-1, -1), "(-1, -1) - negative");
  runTest(a, b, c, Point(10, 10), "(10, 10) - on the extended hypotenuse");
  runTest(a, b, c, Point(0, 11), "( 0, 11) - above C");
  runTest(a, b, c, Point(11, 0), "(11,  0) - right of B");

  std::cout << std::endl;
  // Edge cases
  runTest(a, b, c, Point(0, 0), "(0, 0) - vertex A");
  runTest(a, b, c, Point(10, 0), "(10, 0) - vertex A");
  runTest(a, b, c, Point(0, 10), "(0, 10) - vertex A");
  runTest(a, b, c, Point(5, 0), "(5, 0) - midpoint of side AB");
  runTest(a, b, c, Point(5, 5), "(5, 5) - midpoint of hypotenuse BC");

  return 0;
}
