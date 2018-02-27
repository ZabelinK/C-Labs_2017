#ifndef H_TRIANGLE
#define H_TRIANGLE
#include <iostream>
#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t&, const point_t&, const point_t&);
  friend std::ostream& operator<<(std::ostream&, const Triangle&);
  friend bool operator==(const Triangle&, const Triangle&) noexcept;
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void scale(double) override;
  void move(const point_t&) noexcept override;
  void move(double, double) noexcept override;
  point_t getPosVertexA() const noexcept;
  point_t getPosVertexB() const noexcept;
  point_t getPosVertexC() const noexcept;
  void turn(double) noexcept override;
  std::string getName() const override;
  
private:
  point_t vertex_[3];
  void print(std::ostream&) const override;  
};

bool operator==(const Triangle&, const Triangle&) noexcept;
std::ostream& operator <<(std::ostream&, const Triangle&);

#endif
