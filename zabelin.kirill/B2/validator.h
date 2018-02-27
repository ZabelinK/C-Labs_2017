#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "token_t.h"

class Validator
{
public:
  Validator(size_t width_word, size_t width_num);

  token_t operator()(const token_t& token);

private:
  const size_t width_word_;
  const size_t width_num_;
  token_t::type_t type_;
  char last_char_;
};

#endif // VALIDATOR_H
