#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "compositeshape.hpp"
#include "test-compositeshape.hpp"

int main()
{
  Rectangle rect({11,4},4,4);
  CompositeShape comp(rect);
  Circle cir({5,5},10);
  comp.addShape(cir);
  rect.move({4, 6});
  cir.move(10, 10);
  std::cout << rect << cir << comp;
  std::cout << comp;
  test_compositeShape();
  return 0;
};
