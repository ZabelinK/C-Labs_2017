#include "impl.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <functional>
#include <locale>

#include "shapesinfo.h"
#include "streamsaver.h"

std::istream& wsWithOutNL(std::istream& in)
{
  const std::istream::int_type eof = std::istream::traits_type::eof();
  std::streambuf* sb = in.rdbuf();
  std::istream::int_type c = sb->sgetc();

  while((c != eof)
      && (c != '\n')
      && std::isspace(std::istream::traits_type::to_char_type(c), in.getloc()))
  {
    c = sb->snextc();
  }

  if(c == eof)
  {
    in.setstate(std::ios_base::eofbit);
  }

  return in;
}


std::ostream& operator<<(std::ostream& out, const Point& point)
{
  out << " (" << point.x << "; " << point.y << ')';
  return out;
}

std::istream& operator>>(std::istream& in, Point& point)
{
  Point tmp = {0, 0};
  char bracket_left = '\0', bracket_right = '\0', semicolon = '\0';

  in >> wsWithOutNL >> bracket_left
      >> wsWithOutNL >> tmp.x
      >> wsWithOutNL >> semicolon
      >> wsWithOutNL >> tmp.y
      >> wsWithOutNL >> bracket_right;

  if((bracket_left != '(') || (semicolon != ';') || (bracket_right != ')'))
  {
    in.clear();
    in.setstate(std::ios_base::failbit);
  }
  else
  {
    std::swap(point, tmp);
  }

  return in;
}

std::istream& operator>>(std::istream& in, Shape& shape)
{
  Shape tmp;
  size_t numbVertex = 0;
  in >> std::ws >> numbVertex;
  if(in.eof())
  {
    return in;
  }
  
  if(in.fail())
  {
    return in;
  }
  else
  {
    tmp.insert(tmp.begin(), numbVertex, {0,0});
    for(size_t i = 0; i < numbVertex; ++i)
    {
      in >> tmp.at(i);
    }
  }

  if(!in.fail())
  {
    std::swap(tmp, shape);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  out << shape.size() << " ";
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  return out;
}

class LessShape
{
public:
  bool operator()(const Shape& shape1, const Shape& shape2) const
  {
    return identifyShape(shape1) < identifyShape(shape2);
  }
};

void doPart2(std::istream& in, std::ostream& out)
{
  StreamSaver save_in(in), save_out(out);

  in >> std::noskipws;

  using namespace std::placeholders;

  std::vector<Shape> shapes{std::istream_iterator<Shape>(in), std::istream_iterator<Shape>()};

  if(in.fail() && !in.eof())
  {
    throw std::invalid_argument("Not correct input data\n");
  }

  ShapesInfo info = std::for_each(shapes.begin(), shapes.end(), ShapesInfo());

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
      std::bind(std::equal_to<unsigned long>(), std::bind(&Shape::size, _1), 5ul)), shapes.end());

  std::vector<Point> points(shapes.size());

  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape& shape)
    {
      return shape.at(0);
    });

  std::sort(shapes.begin(), shapes.end(), LessShape());

  out << "Vertices: " << info.getNumbVertex() << '\n'
      << "Triangles: " << info.getNumbTriangles() << '\n'
      << "Squares: " << info.getNumbSquares() << '\n'
      << "Rectangles: " << info.getNumbRectangles() << '\n'
      << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));
  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
