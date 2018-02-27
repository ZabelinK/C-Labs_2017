#include <iostream>
#include <stdexcept>

#include "impl.h"

int main(int argc, char *argv[])
{
  try
  {
    if(argc > 1)
    {
      switch(std::atoi(argv[1]))
      {
      case 1:
        doPart1(argc, argv);
        break;
      case 2:
        doPart2(argc, argv);
        break;
      case 3:
        doPart3(argc, argv);
        break;
      case 4:
        doPart4(argc, argv);
        break;
      default:
        std::cerr << "Not correct input paranmetrs";
        return 1;
      }
      return 0;
    }
    else
    {
      std::cerr << "Not correct input parametrs";
      return 1;
    }
  }
  catch(const std::exception & err)
  {
    std::cerr << err.what() << '\n';
  }
  return 1;
}
  

