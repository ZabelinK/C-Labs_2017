#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &pos, const double &r) : 
  Shape(pos),
  radius_(r)    
{
  assert(radius_>=0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}
		
rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::getInfo(std::ostream& out) const
{
  out << "Circle ";
  Shape::getInfo(out);
  out << " radius = " << radius_;
}

std::ostream& operator <<(std::ostream& out, const Circle &out_circle)
{
  out_circle.getInfo(out);
  return out; 
}
