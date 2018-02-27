#include "book.h"

#include <algorithm>

#include "errors.h"

const std::string PhoneBook::invalid = "";

PhoneBook::PhoneBook():
  data_({note_with_count({invalid, invalid}, {})})
{}

PhoneBook::const_robust_iterator PhoneBook::cbegin() const
{
  return const_robust_iterator(data_.begin());
}

PhoneBook::const_robust_iterator PhoneBook::cend() const
{
  return const_robust_iterator(--data_.end());
}

PhoneBook::robust_iterator PhoneBook::begin()
{
  return robust_iterator(data_.begin());
}

PhoneBook::robust_iterator PhoneBook::end()
{
  return robust_iterator(--data_.end());
}

bool PhoneBook::empty() const
{
  return data_.begin()->first.name == invalid;
}

void PhoneBook::insert(const const_robust_iterator& iter, const note_t& note)
{
  if(PhoneBook::empty())
  {
    data_.insert(iter.get(), note_with_count(note, {}));
    PhoneBook::makeValidIterators();
  }
  else
  {
    data_.insert(iter.get(), note_with_count(note, {}));
  }
}

void PhoneBook::add(const note_t& note)
{
  if(PhoneBook::empty())
  {
    data_.push_front(note_with_count(note, {}));
    PhoneBook::makeValidIterators();
  }
  else
  {
    data_.insert(--data_.end(), note_with_count(note, {}));
  }
}

void PhoneBook::makeValidIterators()
{
  const_robust_iterator tmp(data_.begin());
  while(!data_.back().second.empty())
  {
    *data_.back().second.front() = tmp;
  }
}

void PhoneBook::erase(const_robust_iterator& iter)
{
  if(data_.front().first.name == invalid)
  {
    throw EmptyError();
  }

  if(iter->name == invalid)
  {
    throw BookMarkError();
  }

  list_iterator pos_erase = iter.get();
  const_robust_iterator tmp = iter;

  if(data_.size() == 2)
  {
    ++tmp;
  }
  else
  {
    ++tmp;
    if(tmp->name == invalid)
    {
      tmp -= 2;
    }
  }

  while(!pos_erase->second.empty())
  {
    *pos_erase->second.front() = tmp;
  }
  data_.erase(pos_erase);
}

PhoneBook::const_robust_iterator::const_robust_iterator(PhoneBook::list_iterator iter):
  iter_(iter)
{
  iter_->second.push_back(this);
  pos_ = --iter_->second.end();
}

PhoneBook::const_robust_iterator::const_robust_iterator(const const_robust_iterator& iter):
  iter_(iter.iter_)
{
  iter_->second.push_back(this);
  pos_ = --iter_->second.end();
}

PhoneBook::const_robust_iterator::~const_robust_iterator()
{
  iter_->second.erase(pos_);
}

PhoneBook::const_robust_iterator& PhoneBook::const_robust_iterator::operator=(PhoneBook::list_iterator iter)
{
  const_robust_iterator tmp(iter);
  const_robust_iterator::swap(tmp);
  return *this;
}

PhoneBook::const_robust_iterator& PhoneBook::const_robust_iterator::operator=(const const_robust_iterator& iter)
{
  const_robust_iterator tmp(iter);
  const_robust_iterator::swap(tmp);
  return *this;
}

PhoneBook::const_robust_iterator& PhoneBook::const_robust_iterator::operator++()
{
  if(iter_->first.name != PhoneBook::invalid)
  {
    const_robust_iterator tmp(std::next(iter_));
    const_robust_iterator::swap(tmp);
  }
  return *this;
}

PhoneBook::const_robust_iterator PhoneBook::const_robust_iterator::operator++(int)
{
  const_robust_iterator tmp(*this);
  ++(*this);
  return tmp;
}

PhoneBook::const_robust_iterator& PhoneBook::const_robust_iterator::operator--()
{
  const_robust_iterator tmp(std::prev(iter_));
  const_robust_iterator::swap(tmp);
  return *this;
}

PhoneBook::const_robust_iterator PhoneBook::const_robust_iterator::operator--(int)
{
  const_robust_iterator tmp(*this);
  --(*this);
  return tmp;
}

PhoneBook::const_robust_iterator PhoneBook::const_robust_iterator::operator+(int i) const
{
  const_robust_iterator tmp(iter_);
  if(i < 0)
  {
    return tmp - (-i);
  }
  for(; i > 0; ++(tmp), --i)
  {}
  return tmp;
}

PhoneBook::const_robust_iterator& PhoneBook::const_robust_iterator::operator+=(int i)
{
  *this = *this + i;
  return *this;
}

PhoneBook::const_robust_iterator PhoneBook::const_robust_iterator::operator-(int i) const
{
  const_robust_iterator tmp(iter_);
  if(i < 0)
  {
    return tmp + (-i);
  }
  for(; i > 0; --(tmp), --i)
  {}

  return tmp;
}

PhoneBook::const_robust_iterator& PhoneBook::const_robust_iterator::operator-=(int i)
{
  *this = *this - i;
  return *this;
}

bool PhoneBook::const_robust_iterator::operator==(const const_robust_iterator& iter) const
{
  return iter_ == iter.iter_;
}

bool PhoneBook::const_robust_iterator::operator!=(const const_robust_iterator& iter) const
{
  return !(*this == iter);
}

const note_t& PhoneBook::const_robust_iterator::operator*() const
{
  return iter_->first;
}

const note_t* PhoneBook::const_robust_iterator::operator->() const
{
  return &iter_->first;
}

const PhoneBook::list_iterator& PhoneBook::const_robust_iterator::get() const
{
  return iter_;
}

void PhoneBook::const_robust_iterator::swap(const_robust_iterator& iter)
{
  std::swap(iter.iter_, iter_);
  std::iter_swap(iter.pos_, pos_);
  std::swap(iter.pos_, pos_);
}

PhoneBook::robust_iterator::robust_iterator(PhoneBook::list_iterator iter):
  const_robust_iterator(iter)
{}

PhoneBook::robust_iterator& PhoneBook::robust_iterator::operator=(PhoneBook::list_iterator iter)
{
  const_robust_iterator::operator=(iter);
  return *this;
}

PhoneBook::robust_iterator& PhoneBook::robust_iterator::operator++()
{
  const_robust_iterator::operator++();
  return *this;
}

PhoneBook::robust_iterator PhoneBook::robust_iterator::operator++(int)
{
  auto tmp(*this);
  const_robust_iterator::operator++();
  return tmp;
}

PhoneBook::robust_iterator& PhoneBook::robust_iterator::operator--()
{
  const_robust_iterator::operator--();
  return *this;
}

PhoneBook::robust_iterator PhoneBook::robust_iterator::operator--(int)
{
  auto tmp(*this);
  const_robust_iterator::operator--();
  return tmp;
}

PhoneBook::robust_iterator PhoneBook::robust_iterator::operator+(int i) const
{
  robust_iterator tmp(iter_);
  if(i < 0)
  {
    return tmp - (-i);
  }
  for(; i > 0; ++(tmp), --i)
  {}
  return tmp;
}

PhoneBook::robust_iterator& PhoneBook::robust_iterator::operator+=(int i)
{
  robust_iterator::operator+=(i);
  return *this;
}

PhoneBook::robust_iterator PhoneBook::robust_iterator::operator-(int i) const
{
  robust_iterator tmp(iter_);
  if(i < 0)
  {
    return tmp + (-i);
  }
  for(; i > 0; ++(tmp), --i)
  {}
  return tmp;
}

PhoneBook::robust_iterator& PhoneBook::robust_iterator::operator-=(int i)
{
  const_robust_iterator::operator-=(i);
  return *this;
}

note_t& PhoneBook::robust_iterator::operator*() const
{
  return iter_->first;
}

note_t* PhoneBook::robust_iterator::operator->() const
{
  return &iter_->first;
}
