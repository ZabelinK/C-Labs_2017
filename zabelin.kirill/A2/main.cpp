#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  try {
    Triangle tri({0, 0}, {10, 0}, {5, 5});
    tri.scale(2);
    std::cout << "Triangle area: " << tri.getArea() << '\n';
  }
  catch (std::invalid_argument &err)
  {
    std::cerr << err.what() << '\n';
  }

  try {
    Rectangle rect({ 3, 3 }, -2, 3);
    rect.scale(0.2);
    std::cout << "Rectangle area: " << rect.getArea() << '\n';
  }
  catch (std::invalid_argument &err)
  {
    std::cerr << err.what() << '\n';
  }

  try {
    Circle cir({ 2, 3 }, 1);
    cir.scale(0.5);
    std::cout << "Circle area: " << cir.getFrameRect().height << '\n';
  }
  catch (std::invalid_argument &err)
  {
    std::cerr << err.what() << '\n';
  }
  
  return 0;
};
