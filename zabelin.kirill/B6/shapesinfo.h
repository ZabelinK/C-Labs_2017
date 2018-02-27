#ifndef SHAPESINFO_H
#define SHAPESINFO_H

#include <vector>
#include <cstdio>

struct Point
{
  int x, y;
};

using Shape = std::vector<Point>;

enum class TypeShape
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  ANOTHER
};

TypeShape identifyShape(const Shape&);

class ShapesInfo
{
public:
  void operator()(const Shape&);

  size_t getNumbVertex() const;
  size_t getNumbTriangles() const;
  size_t getNumbSquares() const;
  size_t getNumbRectangles() const;

private:
  size_t numbAllVertex_;
  size_t numbTriangles_;
  size_t numbSquares_;
  size_t numbRectangles_;
};

#endif // SHAPESINFO_H
