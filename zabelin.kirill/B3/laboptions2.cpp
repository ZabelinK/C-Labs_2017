#include "laboptions.h"

#include <iostream>
#include <list>
#include <iterator>
#include <stdexcept>
#include <algorithm>

template <typename ForwardIterator>
void printDual(ForwardIterator it, ForwardIterator rit, std::ostream & out)
{
  out << *it++;
  if(it != rit)
  {
    out << ' ' << *(--rit);
    if(it != rit)
    {
      out << ' ';
      printDual(it, rit, out);
    }
  }
}

void doPart2(std::ostream & out, std::istream & in)
{
  std::list<int> data{std::istream_iterator<int>(in), std::istream_iterator<int>()};

  const size_t maxSizeList = 20;
  const int minValueElement = 1, maxValueElement = 20;

  if(!in.eof())
  {
    throw std::invalid_argument("Not correct data");
  }

  if(data.empty())
  {
    return;
  }

  if(data.size() > maxSizeList)
  {
    throw std::invalid_argument("Not correct data");
  }

  if(std::find_if(data.begin(), data.end(),
      [&maxValueElement, &minValueElement](const int& i) 
      {
        return (i < minValueElement) || (i > maxValueElement);
      }) != data.end())
  {
    throw std::invalid_argument("Not correct data");
  }

  printDual(data.begin(), data.end(), out);
  out << '\n';
}
