#include <iostream>
#include <cstring>

#include "impl.h"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Invalid parametrs.\n ./lab [1|2]\n";
    return 1;
  }

  try
  {
    if(std::strcmp("1", argv[1]) == 0)
    {
      doPart1(std::cin, std::cout);
    }
    else if(std::strcmp("2", argv[1]) == 0)
    {
      doPart2(std::cin, std::cout);
    }
    else
    {
      std::cerr << "Invalid parametrs " << std::string(argv[1]);
      return 1;
    }
  }
  catch(const std::exception& err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }

  return 0;
}
