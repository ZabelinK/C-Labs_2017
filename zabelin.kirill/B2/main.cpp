#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

#include "token_iterator.h"
#include "format_iterator.h"
#include "validator.h"

int main(int argc, char *argv[])
{
  try
  {
    if((argc > 3) || (argc == 2))
    {
      throw std::invalid_argument("Too many options");
    }

    int width = 40;
    const int min_width = 25;
    
    if(argc == 3)
    {
      if(std::string(argv[1]) != "--line-width")
      {
        throw std::invalid_argument("Not correct option");
      }

      width = std::atoi(argv[2]);

      if(width < min_width)
      {
        throw std::invalid_argument("Not correct width");
      }
    }

    const size_t widthWord = 20, widthNumb = 20;
    std::transform(token_iterator(std::cin), token_iterator(),
        format_iterator(std::cout, width), Validator(widthWord, widthNumb));
  }
  catch(const std::exception & err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }

  return 0;
}
