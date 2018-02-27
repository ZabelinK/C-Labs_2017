#include "square.h"

#include <iostream>

Square::Square(int x, int y):
  Shape(x, y)
{}

void Square::draw(std::ostream& out) const
{
  out << "SQUARE (" << x_ << ";" << y_ << ")";
}

