#include <iostream>
#include <stdexcept>
#include <cmath>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "compositeshape.hpp"
#include "matrixshape.hpp"
#include "polygon.hpp"
int main()
{
  try {
    auto rect = std::make_shared<Rectangle>(point_t{ 3,3 }, 1, 2);
    auto cir = std::make_shared<Circle>(point_t{ 2,2 }, 3);
    CompositeShape comp(rect);
    comp.addShape(cir);
    std::cout << comp;
    comp.remove(1);
    comp.remove(0);
    std::cout << comp;
  }
  catch (...)
  {
    std::cout << '1';
  }
  return 0;
}
