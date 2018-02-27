#define _USE_MATH_DEFINES

#include "polygon.hpp"
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include "detail.hpp"

Polygon::Polygon(const Polygon & pol) noexcept :
  points_(pol.points_)
{}

Polygon::Polygon(const point_t *points, size_t size) :
  points_(size)
{
  Polygon::initialize(points);
}

void Polygon::initialize(const point_t * points)
{
  if(points == nullptr)
  {
    throw std::invalid_argument("Points to nullptr");
  }

  if(points_.getSize() < 3)
  {
    throw std::invalid_argument("Polygon contains less than four points");
  }

  for (size_t i = 0; i < points_.getSize(); i++)
  {
    points_[i] = points[i];
  }  

  unsigned long long int permutation = detail::fact(points_.getSize()) + 1;
  size_t i = 0;
  
  while((--permutation != 0) && !(Polygon::isConvex()))
  {
    std::swap(points_[i], points_[i + 1]);
    i++;
    if(i == (points_.getSize() - 1))
    {
      i = 0;
    }
  }

  if(permutation == 0)
  {
    throw std::invalid_argument("The polygon is not convex. Or it is impossible to determine the location of points.");
  }
  
  if(Polygon::getArea() == 0)
  {
    throw std::invalid_argument("Area is zero");
  }
}

Polygon & Polygon::operator=(const Polygon & pol) noexcept
{
  if(this == &pol)
  {
    return *this;
  }
  
  points_ = pol.points_;
  
  return *this;
}

double Polygon::getArea() const
{
  double area = (points_[points_.getSize() - 1].x + points_[0].x) * (points_[points_.getSize() - 1].y - points_[0].y);
  for(size_t i = 0; i < points_.getSize() - 1; i++)
  {
    area += (points_[i].x + points_[i + 1].x) * (points_[i].y - points_[i + 1].y);
  }
  return 0.5 * fabs(area);
}

rectangle_t Polygon::getFrameRect() const
{
  rectangle_t frame_rect = {points_[0], 0, 0};
      
  for(size_t i = 1; i < points_.getSize(); i++)
  {
    frame_rect.expandRect(points_[i]);
  }
  return frame_rect;
}

void Polygon::scale(double coefficient)
{
  point_t centre_frame_rect = Polygon::getFrameRect().pos;
  if ((coefficient > 0) && (coefficient != 1))
  {
    for(size_t i = 0; i < points_.getSize(); i++)
    {
      points_[i] = { centre_frame_rect.x + (points_[i].x - centre_frame_rect.x) * coefficient,
          centre_frame_rect.y + (points_[i].y - centre_frame_rect.y) * coefficient };
    }
  }
  else if(coefficient != 1)
  {
    throw std::invalid_argument("Not correct arguments for scale (Polygon)");
  }
}

void Polygon::move(const point_t &pos)
{
  point_t centre_frame_rect = Polygon::getFrameRect().pos;
  Polygon::move(pos.x - centre_frame_rect.x, pos.y - centre_frame_rect.y);  
}

void Polygon::move(double dx, double dy)
{
  for(size_t i = 0; i < points_.getSize(); i++)
  {
    points_[i].x += dx;
    points_[i].y += dy;
  }
}

void Polygon::turn(double angle) 
{
  angle = (angle * M_PI) / 180;
  double sin_angle = sin(angle),
    cos_angle = cos(angle);
  point_t pos = { 0,0 };
  for (size_t i = 0; i < points_.getSize(); i++)
  {
    pos.x += points_[i].x;
    pos.y += points_[i].y;
  }
  pos.x /= points_.getSize();
  pos.y /= points_.getSize();

  for(size_t i = 0; i < points_.getSize(); i++)
  {
    points_[i] = {pos.x + (points_[i].x - pos.x) * cos_angle - (points_[i].y - pos.y) * sin_angle,
      pos.y + (points_[i].y - pos.y) * cos_angle + (points_[i].x - pos.x) * sin_angle };
  }
}

std::string Polygon::getName() const
{
  return "Polygon";
}

point_t & Polygon::operator[](const size_t &index) const
{
  return points_[index];
}

size_t Polygon::getSize() const noexcept
{
  return points_.getSize();
}

void Polygon::print(std::ostream& out) const
{
  out << "Polygon\n";
  for(size_t i = 0; i < points_.getSize(); i++)
  {
    out << '(' << points_[i].x << ';' << points_[i].y << ")\n";
  }
}

bool Polygon::isConvex() const 
{
  for (size_t i = 0; i < points_.getSize() - 1; i++)
  {
    double line_pos1 = (points_[i + 1].y - points_[i].y) * (points_[0].x - points_[i].x)
        - (points_[i + 1].x - points_[i].x) * (points_[0].y - points_[i].y);
    double line_pos2 = 0;
    for (size_t j = 1; j < points_.getSize(); j++)
    {
      line_pos2 = (points_[i + 1].y - points_[i].y) * (points_[j].x - points_[i].x)
        - (points_[i + 1].x - points_[i].x) * (points_[j].y - points_[i].y);
      if (line_pos2 * line_pos1 >= 0)
      {
        line_pos1 = line_pos2;
      }
      else
      {
        return false;
      }
    }
  }
  return true;
}

bool operator==(const Polygon& p1, const Polygon& p2) 
{
  if(p1.getSize() == p2.getSize())
  {
    for(size_t i = p1.getSize(); p1.points_[i] == p2.points_[i]; i--)
    {
      if(i == 0)
      {
        return true;
      }
    }
    return false;
  }
  else
  {
    return false;
  }
}

std::ostream& operator<<(std::ostream& out, const Polygon & pol)
{
  pol.print(out);
  return out;
}
