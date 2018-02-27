#include "circle.h"

#include <ostream>

Circle::Circle(int x, int y):
  Shape(x, y)
{}

void Circle::draw(std::ostream& out) const
{
  out << "CIRCLE (" << x_ << ";" << y_ << ")";
}
