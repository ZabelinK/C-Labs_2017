#ifndef H_CIRCLE
#define H_CIRCLE
#include <iostream>
#include "shape.hpp"

class Circle : public Shape
{
  public:
    Circle(const point_t &pos, const double &r);
    friend std::ostream& operator<<(std::ostream& out, const Circle &out_circle);
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
    double radius_;
    void printInfo(std::ostream& out) const;
};

std::ostream& operator <<(std::ostream& out, const Circle &out_circle);

#endif
