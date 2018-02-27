#include "detail.hpp"
#include <stdexcept>
#include <cstdlib>

unsigned long long int detail::fact(long long int n)
{
  if(n < 0)
  {
    throw std::invalid_argument("Not correct param");
  }
  if(n == 0)
  {
    return 1;
  }
  return n * fact(n - 1);
}
