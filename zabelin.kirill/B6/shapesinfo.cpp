#include "shapesinfo.h"

int calculateSqrDistance(const Point& a, const Point& b)
{
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void ShapesInfo::operator ()(const Shape& shape)
{
  numbAllVertex_ += shape.size();
  switch(identifyShape(shape))
  {
  case TypeShape::TRIANGLE:
    ++numbTriangles_;
    break;
  case TypeShape::RECTANGLE:
    ++numbRectangles_;
    break;
  case TypeShape::SQUARE:
    ++numbSquares_;
    ++numbRectangles_;
    break;
  case TypeShape::ANOTHER:
    break;
  }
}

size_t ShapesInfo::getNumbVertex() const
{
  return numbAllVertex_;
}

size_t ShapesInfo::getNumbTriangles() const
{
  return numbTriangles_;
}

size_t ShapesInfo::getNumbSquares() const
{
  return numbSquares_;
}

size_t ShapesInfo::getNumbRectangles() const
{
  return numbRectangles_;
}

TypeShape identifyShape(const Shape& shape)
{
  size_t numbVertex = shape.size();

  if(numbVertex == 3)
  {
    return TypeShape::TRIANGLE;
  }
  else if((numbVertex == 4) && calculateSqrDistance(shape[0], shape[2]) == calculateSqrDistance(shape[1], shape[3]))
  {
    if(calculateSqrDistance(shape[0], shape[1]) == calculateSqrDistance(shape[1], shape[2]))
    {
      return TypeShape::SQUARE;
    }
    else
    {
      return TypeShape::RECTANGLE;
    }
  }

  return TypeShape::ANOTHER;
}
