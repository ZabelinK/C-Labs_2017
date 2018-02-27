#include <iostream>

#include "impl.h"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Not correct parametrs\n";
    return 1;
  }

  try
  {
    switch(std::atoi(argv[1]))
    {
    case 1:
      doPart1(std::cin, std::cout);
      break;
    case 2:
      doPart2(std::cin, std::cout);
      break;
    default:
      std::cerr << "Not correct parametrs\n";
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
