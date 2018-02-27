#include "impl.h"
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <iterator>

void doPart1(int argc, char *argv[])
{
  if(argc != 3)
  {
    throw std::invalid_argument("Not enough parameters\n./lab 1 [ascending|descending]");
  }

  auto direction = detail::parseDirection<long long int>(argv[2]);
  std::vector<long long int> data_vector_a(std::istream_iterator<long long int>(std::cin), 
      std::istream_iterator<long long int>());
 
  if(!std::cin.eof())
  {
    throw std::ios_base::failure("Input error");
  }

  if(data_vector_a.empty())
  {
    return;
  }

  std::vector<long long int> data_vector_b(data_vector_a);
  std::forward_list<long long int> data_list(data_vector_a.begin(), data_vector_a.end());
  
  detail::sort(data_vector_a, detail::AccessWithIndex<std::vector<long long int>>(), direction);
  detail::sort(data_vector_b, detail::AccessWithAt<std::vector<long long int>>(), direction);
  detail::sort(data_list, detail::AccessWithIterator<std::forward_list<long long int>>(), direction);
 
  detail::print(data_vector_a.begin(), data_vector_a.end());
  detail::print(data_vector_b.begin(), data_vector_b.end());
  detail::print(data_list.begin(), data_list.end());
}

