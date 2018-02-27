#include "shape.hpp"
#include<iostream>

Shape::Shape(const point_t &pos) :
 pos_(pos)
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

void Shape::getInfo(std::ostream& out) const
{
  out << "(" << pos_.x << "," << pos_.y << ")";
}

Shape::~Shape()
{
}

std::ostream& operator<<(std::ostream& out, const Shape &out_shape)
{
  out_shape.getInfo(out);
  return out;  
}

