#include "impl.h"

#include <algorithm>
#include <iterator>

#include "factorials.h"

int doPart2(std::istream&, std::ostream& out)
{
  Factorials factorials(10);

  out << *factorials.begin();
  std::for_each(++factorials.begin(), factorials.end(), [&out](unsigned long long i)
    {
      out << ' ' << i;
    });

  out << '\n';

  out << *std::reverse_iterator<Factorials::factorial_iterator>(factorials.end());
  std::for_each(std::reverse_iterator<Factorials::factorial_iterator>(--factorials.end()),
      std::reverse_iterator<Factorials::factorial_iterator>(factorials.begin()),
      [&out](unsigned long long i)
    {
      out << ' ' << i;
    });
  out << '\n';

  return 0;
}
