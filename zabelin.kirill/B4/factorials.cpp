#include "factorials.h"

Factorials::Factorials():
  size_(10)
{}

Factorials::Factorials(size_t size):
  size_(size)
{}

Factorials::factorial_iterator Factorials::begin() const
{
  return factorial_iterator{};
}

Factorials::factorial_iterator Factorials::end() const
{
  return factorial_iterator{} + size_;
}

std::reverse_iterator<Factorials::factorial_iterator> Factorials::rbegin() const
{
  return std::reverse_iterator<factorial_iterator>(end());
}

std::reverse_iterator<Factorials::factorial_iterator> Factorials::rend() const
{
  return std::reverse_iterator<factorial_iterator>(begin());
}

Factorials::factorial_iterator::factorial_iterator():
  pos_(1),
  fact_(1)
{}

Factorials::factorial_iterator& Factorials::factorial_iterator::operator++()
{
  fact_ *= ++pos_;
  return *this;
}

Factorials::factorial_iterator Factorials::factorial_iterator::operator++(int)
{
  factorial_iterator tmp(*this);
  ++(*this);
  return tmp;
}

Factorials::factorial_iterator& Factorials::factorial_iterator::operator--()
{
  if(pos_ == 0)
  {
    throw std::out_of_range("There is no factorial '-1'");
  }

  fact_ /= pos_--;
  return *this;
}

Factorials::factorial_iterator Factorials::factorial_iterator::operator--(int)
{
  factorial_iterator tmp(*this);
  --(*this);
  return tmp;
}

Factorials::factorial_iterator Factorials::factorial_iterator::operator+(int i) const
{
  factorial_iterator tmp(*this);
  if(i < 0)
  {
    return tmp - (-i);
  }
  for(; i > 0; ++tmp, --i)
  {}

  return tmp;
}

Factorials::factorial_iterator Factorials::factorial_iterator::operator-(int i) const
{
  factorial_iterator tmp(*this);
  if(i < 0)
  {
    return tmp + (-i);
  }
  for(; i > 0; --tmp, --i)
  {}

  return tmp;
}

Factorials::factorial_iterator &Factorials::factorial_iterator::operator+=(int i)
{
  *this = *this + i;
  return *this;
}

Factorials::factorial_iterator &Factorials::factorial_iterator::operator-=(int i)
{
  *this = *this - i;
  return *this;
}

bool Factorials::factorial_iterator::operator==(const Factorials::factorial_iterator& iter) const
{
  return pos_ == iter.pos_;
}

bool Factorials::factorial_iterator::operator!=(const Factorials::factorial_iterator& iter) const
{
  return pos_ != iter.pos_;
}

unsigned long long Factorials::factorial_iterator::operator*() const
{
  return fact_;
}
