#ifndef TOKEN_T_H
#define TOKEN_T_H

#include <string>

struct token_t
{
  enum type_t
  {
    WORD,
    NUMB,
    PUNCT,
    DASH,
    INVALID
  };

  type_t type_;
  std::string value_;
  size_t line_, column_;
};

void excludeToken(const token_t&);

#endif // TOKEN_T_H
