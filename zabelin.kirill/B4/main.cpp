#include <iostream>

#include "impl.h"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Not correct number parametrs";
    return 1;
  }

  try
  {
    switch(std::atoi(argv[1]))
    {
    case 1:
      return doPart1(std::cin, std::cout);
    case 2:
      return doPart2(std::cin, std::cout);
    default:
      std::cerr << "Not correct parametr\n";
      return 1;
    }
  }
  catch(const std::exception& err)
  {
    std::cerr << err.what() << "\n";
  }
  catch(...)
  {
    std::cerr << "Unknown exception\n";
  }

  return 1;
}
