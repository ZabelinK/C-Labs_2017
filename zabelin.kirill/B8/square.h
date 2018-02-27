#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Square : public Shape
{
public:
  Square(int x, int y);
  void draw(std::ostream&) const override;
};

#endif // RECTANGLE_H
