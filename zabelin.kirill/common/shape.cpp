#include "shape.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Shape &out_shape)
{
  out_shape.print(out);
  return out;
}
