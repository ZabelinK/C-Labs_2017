#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "circle.hpp"
	
Circle::Circle(const point_t &pos, const double &r) : 
  Shape(pos),
  radius_(r)    
{
  if(radius_ <= 0)
  {
    radius_ = 1;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_ * coefficient_ * coefficient_;
}
		
rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_ * coefficient_, 2 * radius_ * coefficient_};
}

void Circle::printInfo(std::ostream& out) const
{
  out << "Coordinates centre (" << pos_.x << ","
    << pos_.y * coefficient_ << ") R = "
    << radius_ * coefficient_;
}

double Circle::getRadius() const
{
  return radius_ * coefficient_;
}

std::ostream& operator <<(std::ostream& out, const Circle &out_circle)
{
  out_circle.printInfo(out);
  return out; 
}
