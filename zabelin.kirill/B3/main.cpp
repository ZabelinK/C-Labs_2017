#include <iostream>
#include <stdexcept>
#include <cstring>

#include "laboptions.h"

int main(int argc, char *argv[])
{
  try
  {
    if(argc != 2)
    {
      std::cerr << "Must only one parametr";
      return 1;
    }

    if(std::strcmp(argv[1], "1") == 0)
    {
      doPart1(std::cout, std::cin);
    }
    else if(std::strcmp(argv[1], "2") == 0)
    {
      doPart2(std::cout, std::cin);
    }
    else
    {
      std::cerr << "Invalid argument. Need 1 or 2";
      return 1;
    }
  }
  catch(const std::exception & err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }

  return 0;
}
