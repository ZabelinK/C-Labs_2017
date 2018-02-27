#ifndef TOKEN_ITERATOR_H
#define TOKEN_ITERATOR_H

#include <iterator>
#include <memory>
#include <locale>
#include "token_t.h"

class token_iterator : public std::iterator<std::input_iterator_tag, token_t>
{
public:
  token_iterator();
  token_iterator(std::istream &);

  bool operator==(const token_iterator &) const;
  bool operator!=(const token_iterator &) const;

  token_iterator& operator++();
  token_iterator operator++(int);
  
  const token_t& operator*() const noexcept;
  const token_t* operator->() const noexcept;

private:
  struct shared_data
  {
    token_t iter_value_;
    std::istream* in_;
    const std::locale locale_;
    bool ok_;
  
    shared_data();
    shared_data(std::istream &);
  };

  std::shared_ptr<shared_data> data_;

  void readToken();
  void readNumb();
  char readChar();
};

#endif // TOKEN_ITERATOR_H
