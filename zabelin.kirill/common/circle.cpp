#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t &pos, double r) :
  pos_(pos),
  radius_(r)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Not correct arguments (Circle)");
  }
}

double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::move(const point_t &pos) noexcept
{
  pos_ = pos;
}

void Circle::move(double dx, double dy) noexcept
{
  pos_ = {pos_.x + dx, pos_.y + dy};
}

void Circle::scale(double coefficient)
{
  if ((coefficient > 0) && (coefficient != 1))
  {
    radius_ *= coefficient;
  }
  else if(coefficient != 1)
  {
    throw std::invalid_argument("Not correct arguments for scale (Circle)");
  }
}

void Circle::turn(double /*angle*/) noexcept
{
}

std::string Circle::getName() const
{
  return "Circle";
}

bool operator==(const Circle & cir1, const Circle & cir2) noexcept
{
  return ((cir1.pos_ == cir2.pos_) && isClose(cir1.radius_, cir2.radius_));
}

void Circle::print(std::ostream& out) const
{
  out << "Circle " << "pos = " << pos_.x << " "
	  << pos_.y << " radius = " << radius_;
}

std::ostream& operator <<(std::ostream& out, const Circle &out_circle)
{
  out_circle.print(out);
  return out;
}
