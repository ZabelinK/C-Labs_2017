#ifndef H_POLYGON
#define H_POLYGON
#include "shape.hpp"
#include <cstdlib>
#include "detail.hpp"

class Polygon : public Shape
{
public:
  Polygon(const Polygon &) noexcept;
  Polygon(Polygon&&) = default;
  Polygon(const point_t *, size_t) ;
  template<size_t size>
  Polygon(const point_t(&)[size]);
  Polygon & operator=(Polygon&&) = default;
  Polygon & operator=(const Polygon &) noexcept;
  friend std::ostream& operator<<(std::ostream&, const Polygon &);
  friend bool operator==(const Polygon &, const Polygon &);
  point_t & operator[](const size_t &) const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void scale(double coefficient) override;
  void move(const point_t &) override;
  void move(double dx, double dy) override;
  void turn(double angle_degrees) override;
  std::string getName() const override;
  size_t getSize() const noexcept;
  
private:
  detail::TempArray<point_t> points_;
  void print(std::ostream&) const override;
  void initialize(const point_t *);
  bool isConvex() const;
};

bool operator==(const Polygon&, const Polygon&);
std::ostream& operator<<(std::ostream&, const Polygon &);

template<size_t size>
Polygon::Polygon(const point_t (&points)[size]):
  points_(size)
{
  Polygon::initialize(&points[0]);
}

#endif
