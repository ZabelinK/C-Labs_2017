#ifndef H_CIRCLE
#define H_CIRCLE
#include <iostream>
#include "shape.hpp"

class Circle : public Shape
{
  public:
    friend std::ostream& operator<<(std::ostream& out, const Circle &out_circle);
    Circle(const point_t &pos, const double &r);
    double getArea() const;
    rectangle_t getFrameRect() const;
    
  private:
    double radius_;
    void getInfo(std::ostream& out) const;
};

std::ostream& operator <<(std::ostream& out, const Circle &out_circle);

#endif
