#include "impl.h"

#include <unordered_set>
#include <string>
#include <algorithm>
#include <iterator>

void doPart1(std::istream& in, std::ostream& out)
{
  std::unordered_set<std::string> words{std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()};

  if(!in.eof())
  {
    throw std::ios_base::failure("Invalid input data");
  }

  std::copy(words.cbegin(), words.cend(), std::ostream_iterator<std::string>(out, "\n"));
}
