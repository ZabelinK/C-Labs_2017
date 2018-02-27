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
    virtual void getInfo(std::ostream& out) const;
    virtual void move(const point_t &end_pos);
    virtual void move(const double &delta_x, const double &delta_y);
    virtual ~Shape() = 0; 
  
  protected:
    point_t pos_;
    Shape(const point_t &pos);
};

std::ostream& operator<<(std::ostream& out, const Shape &out_shape);

#endif
