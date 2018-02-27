#ifndef H_SHAPE
#define H_SHAPE
#include <iostream>
#include "base-types.hpp"
class Shape 
{
  public:
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0; 
    virtual void printInfo(std::ostream& out) const;
    void scale(const double &coef);
    void move(const point_t &end_pos);
    void move(const double &delta_x, const double &delta_y);
    friend std::ostream& operator<<(std::ostream& out, const Shape &out_shape);
    virtual ~Shape() = 0;
    
  protected:
    point_t pos_;
    double coefficient_;
    Shape(const point_t &pos);
};
std::ostream& operator<<(std::ostream& out, const Shape &out_shape);
#endif
