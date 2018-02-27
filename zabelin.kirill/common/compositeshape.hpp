#ifndef H_COMPOSITE_SHAPE
#define H_COMPOSITE_SHAPE
#include <memory>
#include "shape.hpp"

class CompositeShape : public Shape
{
public:
  CompositeShape(const CompositeShape&);
  CompositeShape(CompositeShape&&);
  CompositeShape(const std::shared_ptr<Shape>&);
  CompositeShape & operator=(const CompositeShape&);
  CompositeShape & operator=(CompositeShape&&);
  ~CompositeShape();
  std::shared_ptr<Shape> operator[](const size_t&) const;
  friend std::ostream& operator<<(std::ostream&, const CompositeShape&);
  friend bool operator==(const CompositeShape&, const CompositeShape&);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t&) override;
  void move(double dx, double dy) override;
  void scale(double coefficient) override;
  void addShape(const std::shared_ptr<Shape>&);
  void addShape(const CompositeShape&) = delete;
  void remove(const size_t& index);
  size_t getSize() const noexcept;
  void turn(double angle_degrees) override;
  std::string getName() const override;

private:
  class Impl;
  std::unique_ptr<Impl> impl_ptr_;
  using ptr_shape = std::shared_ptr<Shape>;
  void print(std::ostream&) const override;
};

bool operator==(const CompositeShape&, const CompositeShape&);
std::ostream& operator<<(std::ostream&, const CompositeShape&);

#endif
