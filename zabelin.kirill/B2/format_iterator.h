#ifndef FORMAT_ITERATOR_H
#define FORMAT_ITERATOR_H

#include <iterator>
#include <vector>
#include <memory>

#include "token_t.h"

class format_iterator : public std::iterator<std::output_iterator_tag, token_t>
{
public:
  format_iterator(std::ostream& out, size_t width);
  format_iterator& operator=(const token_t& value);

  format_iterator& operator*();
  
  format_iterator& operator++();
  format_iterator& operator++(int);
  
private:
  struct shared_data
  {
    std::ostream *out_;
    const size_t width_;
    std::vector<char> buf_;
    std::vector<char>::iterator last_token_;
    shared_data(std::ostream&, size_t);
    ~shared_data();
  };

  std::shared_ptr<shared_data> data_;
};

#endif // FORMAT_ITERATOR_H
