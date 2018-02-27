#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>

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
  return M_PI * radius_ * radius_;
}
		
rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::scale(const double &coefficient)
{
  if(coefficient > 0 && coefficient != 1)
  {
    radius_ *= coefficient;
  }
}

void Circle::printInfo(std::ostream& out) const
{
  out << "Circle ";
  Shape::printInfo(out);
  out << " radius = " << radius_ << " area = " << getArea() << '\n';
}

Shape* Circle::clone() const
{
  Shape *clon = new Circle(pos_, radius_);
  return clon;
}

void Circle::move(const point_t &end_pos)
{
  Shape::move(end_pos);
}

void Circle::move(const double &delta_x, const double &delta_y)
{
  Shape::move(delta_x, delta_y);  
}

double Circle::getUpY() const
{
  return pos_.y + radius_;
}

double Circle::getDownY() const
{
  return pos_.y - radius_;
}

double Circle::getLeftX() const
{
  return pos_.x - radius_;
}

double Circle::getRightX() const
{
  return pos_.x + radius_;
}

std::ostream& operator <<(std::ostream& out, const Circle &out_circle)
{
  out_circle.printInfo(out);
  return out; 
}
