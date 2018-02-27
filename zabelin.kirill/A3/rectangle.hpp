#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include "shape.hpp"

class Rectangle : public Shape
{
  public:
    Rectangle(const point_t &pos, const double &height, const double &width);	
    friend std::ostream& operator<<(std::ostream& out, const Rectangle &out_rectangle);
    double getArea() const;
    rectangle_t getFrameRect() const;
    Shape* clone() const;
    void scale(const double &coefficient);
    void move(const point_t &end_pos);
    void move(const double &delta_x, const double &delta_y);
    double getUpY() const;
    double getDownY() const;
    double getLeftX() const;
    double getRightX() const;
    
  private:
    double height_;
    double width_;
    void printInfo(std::ostream& out) const;
};

std::ostream& operator <<(std::ostream& out, const Rectangle &out_rectangle);

#endif
