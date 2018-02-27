#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include "shape.hpp"

class Rectangle : public Shape
{
  public:
    friend std::ostream& operator<<(std::ostream& out, const Rectangle &out_rectangle);
    Rectangle(const point_t &pos, const double &height, const double &width);	
    double getArea() const;
    rectangle_t getFrameRect() const;	
    
  private:
    double height_;
    double width_;
    void getInfo(std::ostream& out) const;
};

std::ostream& operator <<(std::ostream& out, const Rectangle &out_rectangle);

#endif
