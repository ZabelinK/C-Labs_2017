#include "triangle.hpp"
#include <cmath>
#include <cassert>
Triangle::Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c) :
  Shape({(pos_a.x + pos_b.x + pos_c.x) / 3, (pos_a.y + pos_b.y + pos_c.y) / 3}),
  pos_a_(pos_a),
  pos_b_(pos_b),
  pos_c_(pos_c)
{
  assert((pos_a_.x != pos_b_.x || pos_a_.x != pos_c_.x || pos_b_.x != pos_c_.x) 
    && (pos_a_.y != pos_b_.y || pos_a_.y != pos_c_.y || pos_b_.y != pos_c_.y));
}

double Triangle::getArea() const
{
  return fabs(0.5 * ((pos_a_.x - pos_c_.x) * (pos_b_.y - pos_c_.y) - (pos_b_.x - pos_c_.x) * (pos_a_.y - pos_c_.y)));
}

rectangle_t Triangle::getFrameRect() const
{
  double min_x = pos_a_.x;
  if(min_x >= pos_b_.x)
  {
    min_x = pos_b_.x;
    if(min_x > pos_c_.x)
    {
      min_x = pos_c_.x;
    }
  }
  double min_y = pos_a_.y;
  if(min_y >= pos_b_.y)
  {
    min_y = pos_b_.y;
    if(min_y > pos_c_.y)
    {
      min_y = pos_c_.y;
    }
  }
  return {{min_x + ((fabs(pos_a_.x - pos_b_.x) + fabs(pos_a_.x - pos_c_.x) + fabs(pos_c_.x - pos_b_.x)) / 4),
    min_y + ((fabs(pos_a_.y - pos_b_.y) + fabs(pos_a_.y - pos_c_.y) + fabs(pos_c_.y - pos_b_.y)) / 4)}, 
    (fabs(pos_a_.x - pos_b_.x) + fabs(pos_a_.x - pos_c_.x) + fabs(pos_c_.x - pos_b_.x)) / 2 ,
    (fabs(pos_a_.y - pos_b_.y) + fabs(pos_a_.y - pos_c_.y) + fabs(pos_c_.y - pos_b_.y)) / 2 };
}

void Triangle::move(const point_t &end_pos)
{
  pos_a_.x += (end_pos.x - pos_.x);
  pos_a_.y += (end_pos.y - pos_.y);
  pos_b_.x += (end_pos.x - pos_.x);
  pos_b_.y += (end_pos.y - pos_.y);
  pos_c_.x += (end_pos.x - pos_.x);
  pos_c_.y += (end_pos.y - pos_.y);
  Shape::move(end_pos);
}

void Triangle::move(const double &delta_x, const double &delta_y)
{
  move({pos_.x + delta_x, pos_.y + delta_y});
}

void Triangle::getInfo(std::ostream& out) const
{
  out << "Triangle ";
  Shape::getInfo(out);
  out << " A:(" << pos_a_.x << ';' << pos_a_.y 
    << ") B:(" << pos_b_.x << ';' << pos_b_.y 
    << ") C:(" << pos_c_.x << ';' << pos_c_.y << ")"; 
}

std::ostream& operator<<(std::ostream& out, const Triangle &out_triangle)
{
  out_triangle.getInfo(out);
  return out;
}
