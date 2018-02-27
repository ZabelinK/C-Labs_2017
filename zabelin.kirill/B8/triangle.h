#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
public:
  Triangle(int x, int y);
  void draw(std::ostream &) const override;
};

#endif // TRIANGLE_H
