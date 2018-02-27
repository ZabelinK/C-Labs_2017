#ifndef H_TRIANGLE
#define H_TRIANGLE
#include <iostream>
#include "shape.hpp"

class Triangle : public Shape
{
  public:
    friend std::ostream& operator<<(std::ostream& out, const Triangle &out_triangle);
    Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &end_pos);
    void move(const double &delta_x, const double &delta_y);
    
  private:
    point_t pos_a_, pos_b_, pos_c_;
    void getInfo(std::ostream& out) const;
};

std::ostream& operator <<(std::ostream& out, const Triangle &out_circle);

#endif
