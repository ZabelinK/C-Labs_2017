#include "impl.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iterator>
void doPart3(int /*argc*/, char ** /*argv*/)
{
  std::vector<long long int> data_vector(std::istream_iterator<long long int>(std::cin), 
      std::istream_iterator<long long int>());
 
  if(!std::cin.eof())   
  {          
    throw std::ios_base::failure("Input error");   
  }

  if(data_vector.empty())
  {
    return;
  }

  if(data_vector.back() != 0)
  {
    throw std::invalid_argument("missing zero");
  }
  
  data_vector.pop_back();

  if(data_vector.empty())
  {
    return;
  }

  if(data_vector.back() == 1)
  {
    for(auto it = data_vector.begin(); it != data_vector.end();)
    {
      if(*it % 2 == 0)
      {
        it = data_vector.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }
  else if(data_vector.back() == 2)
  {
    size_t count = 0;
    for(auto i = data_vector.begin(); i < data_vector.end(); ++i)
    {
      if(*i % 3 == 0)
      {
        ++count;
      }
    }
    data_vector.insert(data_vector.end(), 3 * count, 0);
    auto i = data_vector.rbegin();
    auto j = data_vector.rbegin() + 3 * count;
    while(i != j)
    {
      if(*j % 3 == 0)
      {
        for(size_t count = 0; count < 3; ++count, ++i)
        {
          *i = 1;
        }
      }
      *(i++) = *(j++);
    }
  }

  detail::print(data_vector.begin(), data_vector.end());
}

