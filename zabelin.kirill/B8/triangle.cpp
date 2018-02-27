#include "triangle.h"

#include <iostream>

Triangle::Triangle(int x, int y):
  Shape(x, y)
{}

void Triangle::draw(std::ostream& out) const
{
  out << "TRIANGLE (" << x_ << ";" << y_ << ")";
}
