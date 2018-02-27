#include "impl.h"

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <sstream>

#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"

using shape_ptr = std::shared_ptr<Shape>;

struct type_shape
{
  std::string type;
};

std::istream& operator>>(std::istream& in, type_shape& type)
{
  char c = in.get();
  while(std::isalpha(c, in.getloc()))
  {
    type.type.push_back(c);
    c = in.get();
  }
  in.unget();
  return in;
}

std::istream& operator>>(std::istream& in, shape_ptr& shape) 
{
  shape = nullptr;
  in >> std::ws;

  std::string line_str;
  std::getline(in, line_str);

  if(line_str.empty())
  {
    return in;
  }

  std::stringstream line(line_str);

  type_shape type;
  char left_bracket = '\0', right_bracket = '\0', semicolon = '\0';
  int x = 0, y = 0;

  line >> type >> left_bracket >> x >> semicolon >> y >> right_bracket;

  if((left_bracket != '(') || (semicolon != ';') || (right_bracket != ')'))
  {
    return in;
  }

  if(type.type == "CIRCLE")
  {
    shape.reset(new Circle(x, y));
  }
  else if(type.type == "TRIANGLE")
  {
    shape.reset(new Triangle(x, y));
  }
  else if(type.type == "SQUARE")
  {
    shape.reset(new Square(x, y));
  }
  else
  {}

  return in;
}

std::ostream& operator <<(std::ostream& out, const shape_ptr& shape)
{
  shape->draw(out);
  return out;
}

void doPart2(std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;

  std::vector<shape_ptr> shapes{std::istream_iterator<shape_ptr>(in), std::istream_iterator<shape_ptr>()};

  std::string error_lines;
  std::for_each(shapes.begin(), shapes.end(), [&error_lines](const shape_ptr& shape)
    {
      static int counter_lines = 1;
      if(!shape)
      {
        error_lines += (' ' + std::to_string(counter_lines));
      }
      ++counter_lines;
    });

  if(!error_lines.empty())
  {
    throw std::ios_base::failure("Wrong input lines:" 
        + error_lines 
        + "\nUse format: [CIRCLE|TRIANGLE|SQUARE] (x;y)");
  }

  out << "Original:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<shape_ptr>(out, "\n"));

  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isMoreLeft,
      std::bind(&shape_ptr::operator*, _1), std::bind(&shape_ptr::operator *, _2)));
  out << "Left-Right:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<shape_ptr>(out, "\n"));

  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isMoreLeft,
      std::bind(&shape_ptr::operator*, _2), std::bind(&shape_ptr::operator *, _1)));
  out << "Right-Left:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<shape_ptr>(out, "\n"));

  std::sort(shapes.begin(), shapes.end(),  std::bind(&Shape::isUpper,
      std::bind(&shape_ptr::operator*, _1), std::bind(&shape_ptr::operator *, _2)));
  out << "Top-Bottom:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<shape_ptr>(out, "\n"));

  std::sort(shapes.begin(), shapes.end(),  std::bind(&Shape::isUpper,
      std::bind(&shape_ptr::operator*, _2), std::bind(&shape_ptr::operator *, _1)));
  out << "Bottom-Top:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<shape_ptr>(out, "\n"));
}
