#ifndef H_BASE_TYPES
#define H_BASE_TYPES

#include <iostream>

bool isClose(double, double);

struct point_t {
  double x, y;
  double getDistance(const point_t&) const noexcept;
};

std::ostream& operator<<(std::ostream&, const point_t&);
bool operator==(const point_t &, const point_t &);
bool operator!=(const point_t &, const point_t &);

struct rectangle_t {
  point_t pos;
  double height, width;
  void expandRect(const point_t &pos) noexcept;
};

std::ostream& operator<<(std::ostream&, const rectangle_t&);
bool operator==(const rectangle_t &, const rectangle_t &);
bool operator!=(const rectangle_t &, const rectangle_t &);
#endif
