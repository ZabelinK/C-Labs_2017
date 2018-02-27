#ifndef CIRCLE_H
#define CIRCLE_H

#include <cstdio>
#include "shape.h"

class Circle : public Shape
{
public:
  Circle(int x, int y);
  void draw(std::ostream&) const override;
};

#endif // CIRCLE_H
