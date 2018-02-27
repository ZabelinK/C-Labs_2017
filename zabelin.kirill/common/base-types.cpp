#include "base-types.hpp"
#include <iostream>
#include <limits>
#include <cmath>

double point_t::getDistance(const point_t &pos) const noexcept
{
  return sqrt((pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y));
}

bool isClose(double d1, double d2)
{
  return (fabs(d1 - d2) <= std::numeric_limits<double>::epsilon() * std::fmax(abs(d1), abs(d2)));
}

std::ostream& operator<<(std::ostream& out, const point_t &pos)
{
  out << '(' << pos.x << ';' << pos.y << ')';
  return out;
}

bool operator==(const point_t & a, const point_t & b)
{
  return (isClose(a.x, b.x) && isClose(a.y, b.y));
}

bool operator!=(const point_t & a, const point_t & b)
{
  return !(a == b);
}

void rectangle_t::expandRect(const point_t &posit) noexcept
{
  if ((posit.y > pos.y + width / 2) || (posit.y < pos.y - width / 2))
  {
    pos.y = posit.y + ((width / 2 + fabs(posit.y - pos.y)) / 2) * ((pos.y - posit.y < 0) ? -1 : 1);
    width = fabs(posit.y - pos.y) * 2;
  }
  if ((posit.x > pos.x + height / 2) || (posit.x < pos.x - height / 2))
  {
    pos.x = posit.x + ((height / 2 + fabs(posit.x - pos.x)) / 2) * ((pos.x - posit.x < 0) ? -1 : 1);
    height = fabs(posit.x - pos.x) * 2;
  }
}

std::ostream& operator<<(std::ostream& out, const rectangle_t &rect)
{
  out << rect.pos << ' ' << rect.height << ' ' << rect.width;
  return out;
}

bool operator==(const rectangle_t & r1, const rectangle_t & r2)
{
  return ((r1.pos == r2.pos) && isClose(r1.height, r2.height) && isClose(r1.width, r2.width));
}

bool operator!=(const rectangle_t & r1, const rectangle_t & r2)
{
  return !(r1 == r2);
}
