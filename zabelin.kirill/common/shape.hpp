#ifndef H_SHAPE
#define H_SHAPE
#include <iostream>
#include <string>
#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  friend std::ostream& operator<<(std::ostream&, const Shape&);
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const= 0;
  virtual void print(std::ostream&) const = 0;
  virtual void scale(double) = 0;
  virtual void move(const point_t&) = 0;
  virtual void move(double, double) = 0;
  virtual void turn(double) = 0;
  virtual std::string getName() const = 0;
};

std::ostream& operator<<(std::ostream&, const Shape&);

#endif
