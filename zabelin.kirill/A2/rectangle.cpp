#include <iostream>
#include "rectangle.hpp"
Rectangle::Rectangle(const point_t &pos, const double &height, const double &width) :
  Shape(pos),
  height_(height),
  width_(width)
{
  if(height_ <= 0)
  {
    height_ = 1;
  }
  if(width_ <= 0)
	
  {
    width_ = 1;
  }
}
	
double Rectangle::getArea() const
{
  return width_ * height_ * coefficient_ * coefficient_;
}
		
rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, height_ * coefficient_, width_ * coefficient_};
}
void Rectangle::printInfo(std::ostream& out) const
{
  out << "Coordinates centre (" << pos_.x << ","
    << pos_.y << ") height = "
    << height_ * coefficient_ << " width = "
    << width_ * coefficient_;
}

double Rectangle::getHeight() const
{
  return height_ * coefficient_;
}

double Rectangle::getWidth() const
{
  return width_ * coefficient_;
}

std::ostream& operator <<(std::ostream& out, const Rectangle &out_rectangle)
{
  out_rectangle.printInfo(out);
  return out; 
}
