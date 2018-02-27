#include "rectangle.hpp"
#include <iostream>

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
  return width_ * height_;
}
		
rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, height_, width_};
}

void Rectangle::printInfo(std::ostream& out) const
{
  out << "Rectangle ";
  Shape::printInfo(out); 
  out << " heigt = " << height_ << " width = " << width_
    << " area = " << getArea() << '\n';
}

void Rectangle::scale(const double &coefficient)
{
  if(coefficient > 0 && coefficient != 1)
  {
    height_ *= coefficient;
    width_ *= coefficient;
  }
}

Shape* Rectangle::clone() const
{
  Shape *clon = new Rectangle(pos_, height_, width_);
  return clon;
}

void Rectangle::move(const point_t &end_pos)
{
  Shape::move(end_pos);
}

void Rectangle::move(const double &delta_x, const double &delta_y)
{
  Shape::move(delta_x, delta_y);
}

double Rectangle::getUpY() const
{
  return pos_.y + height_ / 2;
}

double Rectangle::getDownY() const
{
  return pos_.y - height_ / 2;
}

double Rectangle::getLeftX() const
{
  return pos_.x - width_ / 2;
}

double Rectangle::getRightX() const
{
  return pos_.x + width_ / 2;
}

std::ostream& operator <<(std::ostream& out, const Rectangle &out_rectangle)
{
  out_rectangle.printInfo(out);
  return out; 
}
