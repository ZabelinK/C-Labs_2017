#define _USE_MATH_DEFINES

#include "triangle.hpp"
#include <cmath>
#include <stdexcept>

Triangle::Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c) :
  vertex_{pos_a, pos_b, pos_c}
{
  if (getArea() == 0)
  {
    throw std::invalid_argument("Not correct arguments (Triangle)");
  }
}

double Triangle::getArea() const noexcept
{
  return fabs(0.5 * ((vertex_[0].x - vertex_[2].x) * (vertex_[1].y - vertex_[2].y) 
        - (vertex_[1].x - vertex_[2].x) * (vertex_[0].y - vertex_[2].y)));
}

rectangle_t Triangle::getFrameRect() const noexcept
{
  rectangle_t frame_rect = {vertex_[0], 0, 0};
  frame_rect.expandRect(vertex_[1]);
  frame_rect.expandRect(vertex_[2]);
  return frame_rect;
}

void Triangle::move(const point_t &end_pos) noexcept
{
  point_t center =Triangle::getFrameRect().pos;
  Triangle::move(end_pos.x - center.x, end_pos.y - center.y);
}

void Triangle::move(double dx, double dy) noexcept
{
  for (int i = 0; i < 3; i++)
  {
	  vertex_[i].x += dx;
	  vertex_[i].y += dy;
  }
}

void Triangle::scale(double coefficient)
{
  point_t center = Triangle::getFrameRect().pos;

  if ((coefficient > 0) && (coefficient != 1))
  {
    for(int i = 0; i < 3; i++)
    {
      vertex_[i] = { center.x + (vertex_[i].x - center.x) * coefficient,
          center.y + (vertex_[i].y - center.y) * coefficient};
    }
  }
  else if(coefficient != 1)
  {
    throw std::invalid_argument("Not correct arguments for scale (Triangle)");
  }
}

void Triangle::print(std::ostream& out) const
{
  out << "Triangle "
      << " A:(" << vertex_[0].x << ';' << vertex_[0].y 
      << ") B:(" << vertex_[1].x << ';' << vertex_[1].y 
      << ") C:(" << vertex_[2].x << ';' << vertex_[2].y << ")";
}

point_t Triangle::getPosVertexA() const noexcept
{
  return vertex_[0];
}

point_t Triangle::getPosVertexB() const noexcept
{
  return vertex_[1];
}

point_t Triangle::getPosVertexC() const noexcept
{
  return vertex_[2];
}

void Triangle::turn(double angle) noexcept
{
  point_t center = { (vertex_[0].x + vertex_[1].x + vertex_[2].x) / 3,
    (vertex_[0].y + vertex_[1].y + vertex_[2].y) / 3 };
  angle = (angle * M_PI) / 180;
  double sin_angle = sin(angle),
    cos_angle = cos(angle);
  for(int i = 0; i < 3; i++)
  {
    vertex_[i] = { center.x + (vertex_[i].x - center.x) * cos_angle - (vertex_[i].y - center.y) * sin_angle,
      center.y + (vertex_[i].y - center.y) * cos_angle + (vertex_[i].x - center.x) * sin_angle };
  }
}

std::string Triangle::getName() const
{
  return "Triangle";
}

bool operator==(const Triangle & tri1, const Triangle & tri2) noexcept
{
  return (((tri1.vertex_[0] == tri2.vertex_[0]) 
        || (tri1.vertex_[0] == tri2.vertex_[1]) 
        || (tri1.vertex_[0] == tri2.vertex_[2]))
      && ((tri1.vertex_[1] == tri2.vertex_[0])
        || (tri1.vertex_[1] == tri2.vertex_[1])
        || (tri1.vertex_[1] == tri2.vertex_[2]))
      && ((tri1.vertex_[2] == tri2.vertex_[0])
        || (tri1.vertex_[2] == tri2.vertex_[1])
        || (tri1.vertex_[2] == tri2.vertex_[2])));
}

std::ostream& operator<<(std::ostream& out, const Triangle &out_triangle)
{
  out_triangle.print(out);
  return out;
}

