#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t&, double, double);
  friend std::ostream& operator<<(std::ostream&, const Rectangle&);
  friend bool operator==(const Rectangle&, const Rectangle&) noexcept;
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(const point_t&) noexcept override;
  void move(double, double) noexcept override;
  void scale(double) override;
  void turn(double) noexcept override;
  std::string getName() const override;
  
private:
  point_t vertex_[3];
  void print(std::ostream&) const override;
};

bool operator==(const Rectangle&, const Rectangle&) noexcept;
std::ostream& operator <<(std::ostream&, const Rectangle &);

#endif
