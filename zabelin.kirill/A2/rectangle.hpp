#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include "shape.hpp"
class Rectangle : public Shape
{
	
  public:
    Rectangle(const point_t &pos, const double &height, const double &width);	
    double getArea() const;
    rectangle_t getFrameRect() const;	
    void printInfo(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const Rectangle &out_rectangle);
    double getHeight() const;
    double getWidth() const;
    
  private:
    double height_;
    double width_;
};
std::ostream& operator <<(std::ostream& out, const Rectangle &out_rectangle);
#endif
