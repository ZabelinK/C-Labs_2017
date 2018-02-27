#ifndef H_CIRCLE
#define H_CIRCLE
#include <iostream>
#include "shape.hpp"
class Circle : public Shape
{
  public:	
    Circle(const point_t &pos, const double &r);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void printInfo(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const Circle &out_circle);
    double getRadius() const;
    
  private:
    double radius_;
};
std::ostream& operator <<(std::ostream& out, const Circle &out_circle);
#endif
