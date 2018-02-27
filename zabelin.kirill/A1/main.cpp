#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  point_t point = {50, 40};
  double dx = 5, dy = -5;
  Rectangle rect({2, 2}, 8, 9);
  Circle cir({2, 3}, 2);
  Triangle tri({1, 2}, {2, 2}, {2, 1});
  Shape *shape_one = &rect, *shape_two = &cir, *shape_three = &tri;
 
  std::cout << *shape_one << " area: " << shape_one->getArea() << '\n' 
    << *shape_two << " area: " << shape_two->getArea() << '\n'
    << *shape_three << " area: " << shape_three->getArea() << '\n';
      
  shape_one->move(dx, dy);
  shape_two->move(dx, dy);
  shape_three->move(1, 1);
  std::cout << "After moving (double, double):" << '\n' 
    << *shape_one << " area: " << shape_one->getArea() << '\n' 
    << *shape_two << " area: " << shape_two->getArea() << '\n'
    << *shape_three << " area: " << shape_three->getArea() << '\n';  
  shape_one->move(point);
  shape_two->move(point);
  shape_three->move({1.5, 1.5});
  std::cout << "After moving (point_t):" << '\n' 
    << *shape_one << " area: " << shape_one->getArea() << '\n' 
    << *shape_two << " area: " << shape_two->getArea() << '\n'
    << *shape_three << " area: " << shape_three->getArea() << '\n';
    
  rectangle_t rectangle_r = shape_one->getFrameRect();
  rectangle_t rectangle_c = shape_two->getFrameRect();
  rectangle_t rectangle_t = shape_three->getFrameRect();
  std::cout << "Bounding rectangles:" << '\n'
    << "Rectangle " << rectangle_r.pos.x << " " << rectangle_r.pos.y << " heigt = "
    << rectangle_r.height << " width = " << rectangle_r.width << '\n'
    << "Circle " << rectangle_c.pos.x << " " << rectangle_c.pos.y << " heigt = "
    << rectangle_c.height << " width = " << rectangle_c.width << '\n' 
    << "Triangle " << rectangle_t.pos.x << " " << rectangle_t.pos.y << " heigt = "
    << rectangle_t.height << " width = " << rectangle_t.width << '\n';
      
  return 0;
};
