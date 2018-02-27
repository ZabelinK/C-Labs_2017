#ifndef H_COMPOSITE_SHAPE
#define H_COMPOSITE_SHAPE
#include "shape.hpp"

class CompositeShape : public Shape
{
  public:
    CompositeShape(const Shape &new_shape);
    ~CompositeShape();
    friend std::ostream& operator<<(std::ostream& out, const CompositeShape &out_shape);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void addShape(const Shape &new_shape);
    void scale(const double &coefficient);
    void move(const point_t &end_pos);
    void move(const double &delta_x, const double &delta_y);
    double getUpY() const;
    double getDownY() const;
    double getLeftX() const;
    double getRightX() const;
    
  private:
    int size_;
    Shape **mass_;
    double area_;
    void printInfo(std::ostream& out) const;
    Shape* clone() const;
};

std::ostream& operator<<(std::ostream& out, const CompositeShape &out_shape);

#endif
