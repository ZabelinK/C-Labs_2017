#ifndef H_CIRCLE
#define H_CIRCLE
#include <iostream>
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t&, double);
  friend std::ostream& operator<<(std::ostream&, const Circle&);
  friend bool operator==(const Circle&, const Circle&) noexcept;
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(const point_t&) noexcept override;
  void move(double, double) noexcept override;
  void scale(double) override;
  void turn(double) noexcept override;
  std::string getName() const override;

private:
  point_t pos_;
  double radius_;
  void print(std::ostream&) const override;
};

bool operator==(const Circle&, const Circle&) noexcept;
std::ostream& operator <<(std::ostream&, const Circle&);

#endif
