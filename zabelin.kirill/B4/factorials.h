#ifndef FACTORIALS_H
#define FACTORIALS_H

#include <iterator>

class Factorials
{
public:
  
  class factorial_iterator;

  typedef unsigned long long value_type;
  typedef size_t size_type;
  typedef factorial_iterator iterator;
  typedef factorial_iterator const_iterator;
  typedef std::reverse_iterator<factorial_iterator> reverse_iterator;
  typedef std::reverse_iterator<factorial_iterator> const_reverse_iterator;

  class factorial_iterator : public std::iterator<std::bidirectional_iterator_tag,
      unsigned long long, size_t, unsigned long long*, unsigned long long>
  {
  public:
    factorial_iterator();

    factorial_iterator& operator++();
    factorial_iterator operator++(int);

    factorial_iterator& operator--();
    factorial_iterator operator--(int);

    factorial_iterator operator+(int) const;
    factorial_iterator operator-(int) const;

    factorial_iterator& operator+=(int);
    factorial_iterator& operator-=(int);

    bool operator==(const factorial_iterator&) const;
    bool operator!=(const factorial_iterator&) const;

    unsigned long long operator*() const;

  private:
    size_t pos_;
    unsigned long long fact_;
  };

  Factorials();
  Factorials(size_t);

  factorial_iterator begin() const;
  factorial_iterator end() const;
  std::reverse_iterator<factorial_iterator> rbegin() const;
  std::reverse_iterator<factorial_iterator> rend() const;

private:
  size_t size_;
};

#endif // FACTORIALS_H
