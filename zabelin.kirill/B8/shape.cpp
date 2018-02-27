#include "shape.h"

Shape::Shape(int x, int y):
  x_(x),
  y_(y)
{}

bool Shape::isMoreLeft(const Shape& shape)
{
  return x_ < shape.x_;
}

bool Shape::isUpper(const Shape& shape)
{
  return y_ > shape.y_;
}
