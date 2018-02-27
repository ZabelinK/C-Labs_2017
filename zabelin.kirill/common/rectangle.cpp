#define _USE_MATH_DEFINES

#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

Rectangle::Rectangle(const point_t &pos, double height, double width) :
  vertex_{ { pos.x - height / 2, pos.y - width / 2 },
  { pos.x - height / 2, pos.y + width / 2 },
  { pos.x + height / 2, pos.y - width / 2 } }
{
  if ((height <= 0) || (width <= 0))
  {
    throw std::invalid_argument("Not correct arguments (Rectangle)");
  }
}

double Rectangle::getArea() const noexcept
{
  return vertex_[0].getDistance(vertex_[1]) * vertex_[0].getDistance(vertex_[2]);
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  rectangle_t frame_rect = { { vertex_[2].x + (vertex_[1].x - vertex_[0].x),
    vertex_[2].y + (vertex_[1].y - vertex_[0].y) }, 0, 0 };
  for (int i = 0; i < 3; i++)
  {
    frame_rect.expandRect(vertex_[i]);
  }

  return frame_rect;
}

void Rectangle::move(const point_t &pos) noexcept
{
  point_t center = Rectangle::getFrameRect().pos;
  Rectangle::move(pos.x - center.x, pos.y - center.y);
}

void Rectangle::move(double dx, double dy) noexcept
{
  for (int i = 0; i < 3; i++)
  {
    vertex_[i].x += dx;
    vertex_[i].y += dy;
  }
}

void Rectangle::scale(double coefficient)
{
  point_t center = Rectangle::getFrameRect().pos;
  if ((coefficient > 0) && (coefficient != 1))
  {
    for (int i = 0; i < 3; i++)
    {
      vertex_[i] = { center.x + (vertex_[i].x - center.x) * coefficient,
        center.y + (vertex_[i].y - center.y) * coefficient };
    }
  }
  else if (coefficient != 1)
  {
    throw std::invalid_argument("Not correct arguments for scale (Rectangle)");
  }
}

void Rectangle::turn(double angle) noexcept
{
  point_t center = Rectangle::getFrameRect().pos;
  angle = (angle * M_PI) / 180;
  double sin_angle = sin(angle),
    cos_angle = cos(angle);
  for (int i = 0; i < 3; i++)
  {
    vertex_[i] = { center.x + (vertex_[i].x - center.x) * cos_angle - (vertex_[i].y - center.y) * sin_angle,
      center.y + (vertex_[i].y - center.y) * cos_angle + (vertex_[i].x - center.x) * sin_angle };
  }
}

std::string Rectangle::getName() const
{
  return "Rectangle";
}

bool operator==(const Rectangle & rect1, const Rectangle & rect2) noexcept
{
  return ((rect1.vertex_[0] == rect2.vertex_[0])
    && (rect1.vertex_[1] == rect2.vertex_[1])
    && (rect1.vertex_[2] == rect2.vertex_[2]));
}

void Rectangle::print(std::ostream& out) const
{
  point_t center = Rectangle::getFrameRect().pos;
  out << "Rectangle " << "pos = " << center.x << " "
    << center.y << " height " << vertex_[0].getDistance(vertex_[2])
    << " width = " << vertex_[0].getDistance(vertex_[1]);
}

std::ostream& operator <<(std::ostream& out, const Rectangle &out_rectangle)
{
  out_rectangle.print(out);
  return out;
}
