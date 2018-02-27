#ifndef SHAPE_H
#define SHAPE_H

#include <iosfwd>

class Shape
{
public:
  Shape(int x, int y);

  virtual ~Shape() = default;

  bool isMoreLeft(const Shape&);
  bool isUpper(const Shape&);
  virtual void draw(std::ostream&) const = 0;

protected:
  int x_, y_;
};

#endif // SHAPE_H
