#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "compositeshape.hpp"

int main()
{
  auto rect = std::make_shared<Rectangle>(point_t{2,3},5,4);
  CompositeShape comp(rect);
  return 0;
};
