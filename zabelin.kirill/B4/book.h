#ifndef BOOK_H
#define BOOK_H

#include <list>
#include <string>
#include <iterator>


struct note_t
{
  std::string phone_number;
  std::string name;
};

class PhoneBook
{
public:
  static const std::string invalid;

  class const_robust_iterator;
  class robust_iterator;

  friend const_robust_iterator;
  friend robust_iterator;

  typedef unsigned long long value_type;
  typedef size_t size_type;
  typedef robust_iterator iterator;
  typedef const_robust_iterator const_iterator;
  typedef std::reverse_iterator<robust_iterator> reverse_iterator;
  typedef std::reverse_iterator<const_robust_iterator> const_reverse_iterator;

  PhoneBook();

  const_robust_iterator cbegin() const;
  const_robust_iterator cend() const;

  robust_iterator begin();
  robust_iterator end();

  bool empty() const;

  void insert(const const_robust_iterator&, const note_t&);
  void add(const note_t&);
  void erase(const_robust_iterator&);

private:
  using note_with_count = std::pair<note_t, std::list<const_robust_iterator*>>;
  using list = std::list<note_with_count>;
  using list_iterator = std::list<note_with_count>::iterator;

  mutable list data_;

  void makeValidIterators();
};

class PhoneBook::const_robust_iterator : public std::iterator<std::bidirectional_iterator_tag, note_t>
{
public:
  const_robust_iterator(PhoneBook::list_iterator);
  const_robust_iterator(const const_robust_iterator&);
  virtual ~const_robust_iterator();

  const_robust_iterator& operator=(PhoneBook::list_iterator);
  const_robust_iterator& operator=(const const_robust_iterator&);

  const_robust_iterator& operator++();
  const_robust_iterator operator++(int);

  const_robust_iterator& operator--();
  const_robust_iterator operator--(int);

  const_robust_iterator operator+(int) const;
  const_robust_iterator& operator+=(int);

  const_robust_iterator operator-(int) const;
  const_robust_iterator& operator-=(int);

  bool operator==(const const_robust_iterator&) const;
  bool operator!=(const const_robust_iterator&) const;

  const note_t& operator*() const;
  const note_t* operator->() const;

  const PhoneBook::list_iterator& get() const;

protected:
  PhoneBook::list_iterator iter_;
  std::list<const_robust_iterator*>::iterator pos_;

  void swap(const_robust_iterator&);
};

class PhoneBook::robust_iterator : public PhoneBook::const_robust_iterator
{
public:
  robust_iterator(PhoneBook::list_iterator);

  robust_iterator& operator=(PhoneBook::list_iterator);

  robust_iterator& operator++();
  robust_iterator operator++(int);

  robust_iterator& operator--();
  robust_iterator operator--(int);

  robust_iterator operator+(int) const;
  robust_iterator& operator+=(int);

  robust_iterator operator-(int) const;
  robust_iterator& operator-=(int);

  note_t& operator*() const;
  note_t* operator->() const;
};

#endif
