#ifndef LAB_1_IMPL_H
#define LAB_1_IMPL_H

#include <iostream>
#include <functional>
#include <cstring>
namespace detail
{
  template<typename T>
  class AccessWithIndex
  {
  public:
    typename T::reference operator()(T& cont, size_t i)
    {
      return cont[i];
    }
    size_t begin(const T&) const
    {
      return 0;
    }
    size_t end(const T& cont) const
    {
      return cont.size();
    }
  };

  template<typename T>
  class AccessWithAt
  {
  public:
    typename T::reference operator()(T& cont, size_t i)
    {
      return cont.at(i);
    }
    size_t begin(const T&) const
    {
      return 0;
    }
    size_t end(const T& cont) const
    {
      return cont.size();
    }
  };

  template<typename T>
  class AccessWithIterator
  {
  public:
    typename T::reference operator()(T&, typename T::iterator it)
    {
      return *it;
    }
    typename T::iterator begin(T& cont)
    {
      return cont.begin();
    }
    typename T::iterator end(T& cont)
    {
      return cont.end();
    }
  };

  template<typename Container, typename Access, typename Compare>
  void sort(Container& cont, Access access, Compare cmp)
  {
    for(auto i = access.begin(cont); i != access.end(cont); ++i)
    {
      for(auto j = i; j != access.end(cont); ++j)
      {
        if(cmp(access(cont, i), access(cont, j)))
        {
          std::swap(access(cont, i), access(cont, j));
        }
      }
    }
  }

  template<typename Iter>
  void print(Iter begin, Iter end, bool gap = true)
  {
    for(Iter i = begin; i != end; ++i)
    {
      std::cout << *i;
      if(gap)
      {
        std::cout << ' ';
      }
    }
    if((begin != end) && gap)
    {
      std::cout << '\n';
    }
  }

  template<typename T>
  std::function<bool(T,T)> parseDirection(const char* arg)
  {
    if(strcmp(arg, "ascending") == 0)
    {
      return std::function<bool(T,T)>(std::greater<T>());
    }
    if(strcmp(arg, "descending") == 0)
    {
      return std::function<bool(T,T)>(std::less<T>());
    }
    throw std::invalid_argument("Not correct argument");
  }
}

void doPart1(int argc, char *argv[]);
void doPart2(int argc, char *argv[]);
void doPart3(int argc, char *argv[]);
void doPart4(int argc, char *argv[]);

#endif
