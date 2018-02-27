#include<iostream>
#include "shape.hpp"
Shape::Shape(const point_t &pos) :
 pos_(pos),
 coefficient_(1)
{
}

void Shape::move(const point_t &pos)
{
  pos_ = pos;
}

void Shape::move(const double &delta_x, const double &delta_y)
{
  move({delta_x + pos_.x, delta_y + pos_.y});
}

void Shape::printInfo(std::ostream& out) const
{
  out << pos_.x << pos_.y;
}

Shape::~Shape()
{
}

void Shape::scale(const double &coef)
{
  coefficient_ *= coef;
}

std::ostream& operator<<(std::ostream& out, const Shape &out_shape)
{
  out_shape.printInfo(out);
  return out;  
}

