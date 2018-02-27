#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "dataanalysis.h"

int main(int, char *[])
{
  std::vector<long long int> data(std::istream_iterator<long long int>(std::cin),
      std::istream_iterator<long long int>());

  if(!std::cin.eof())
  {
    std::cerr << "Input error";
    return 1;
  }

  DataAnalysis analysis = std::for_each(data.begin(), data.end(), DataAnalysis());
  
  if(analysis.empty())
  {
    std::cout << "No Data\n";
    return 0;
  }

  std::cout << "Max: " << analysis.getMax() << '\n'
       << "Min: " << analysis.getMin() << '\n'
       << std::fixed
       << "Mean: " << analysis.getMean() << '\n'
       << "Positive: " << analysis.getNumbPositive() << '\n'
       << "Negative: " << analysis.getNumbNegative() << '\n'
       << "Odd Sum: " << analysis.getSumOdd() << '\n'
       << "Even Sum: " << analysis.getSumEven() << '\n'
       << "First/Last Equal: " << (analysis.checkFirstEqLast() ? "yes" : "no") << '\n';
  
  return 0;
}
