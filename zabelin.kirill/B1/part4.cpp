#include "impl.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <cstdlib>

void fillRandom(double * array, int size)
{
  srand(time(0));
  while(size != 0)
  {
    array[--size] = (static_cast<double>(rand()) / (RAND_MAX / 2)) - 1.0;
  }
}

void doPart4(int argc, char *argv[])
{
  if(argc != 4)
  {
    throw std::invalid_argument("Not correct parameters\n./lab 4 [ascending|descending] (size)");
  }
  
  auto direction = detail::parseDirection<double>(argv[2]);

  std::vector<double> data_vector(std::stoll(argv[3]));
  fillRandom(data_vector.data(), data_vector.size());
  detail::print(data_vector.begin(), data_vector.end());
  detail::sort(data_vector, detail::AccessWithIterator<std::vector<double>>(), direction);
  detail::print(data_vector.begin(), data_vector.end());
}
