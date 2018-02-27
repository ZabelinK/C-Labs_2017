#ifndef H_SHAPE
#define H_SHAPE
#include <iostream>
#include "base-types.hpp"

class Shape 
{
  public:
    friend std::ostream& operator<<(std::ostream& out, const Shape &out_shape);
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void scale(const double &coefficient) = 0;
    virtual void printInfo(std::ostream& out) const = 0;
    virtual Shape* clone() const = 0;
    virtual void move(const point_t &end_pos);
    virtual void move(const double &delta_x, const double &delta_y);
    point_t getPos();
    virtual ~Shape() = 0;
    virtual double getUpY() const = 0;
    virtual double getDownY() const = 0;
    virtual double getLeftX() const = 0;
    virtual double getRightX() const = 0;
    
  protected:
    point_t pos_;
    Shape(const point_t &pos);
};

std::ostream& operator<<(std::ostream& out, const Shape &out_shape);

#endif
