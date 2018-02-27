#include "impl.h"

#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std::placeholders;

void doPart1(std::istream& in, std::ostream& out)
{
  std::transform(std::istream_iterator<double>(in),
      std::istream_iterator<double>(),
      std::ostream_iterator<double>(out, " "),
      std::bind(std::multiplies<double>(), _1, M_PI));

  if(!in.eof())
  {
    throw std::invalid_argument("Not correct data");
  }
}
