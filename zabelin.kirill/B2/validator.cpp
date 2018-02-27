#include "validator.h"

Validator::Validator(size_t width_word, size_t width_num):
  width_word_(width_word),
  width_num_(width_num),
  type_(token_t::INVALID),
  last_char_('\0')
{}

token_t Validator::operator()(const token_t& token)
{
  switch(token.type_)
  {
  case token_t::NUMB:
    if(token.value_.size() > width_num_)
    {
      excludeToken(token);
    }
    break;
  case token_t::WORD:
    if(token.value_.size() > width_word_)
    {
      excludeToken(token);
    }
    break;
  case token_t::DASH:
    if(type_ == token_t::INVALID)
    {
      excludeToken(token);
    }
    if(token.value_.size() != 3)
    {
      excludeToken(token);
    }
    if(((type_ == token_t::PUNCT) || (type_ == token_t::DASH))
        && (last_char_ != ','))
    {
      excludeToken(token);
    }
    break;
  case token_t::PUNCT:
    if(type_ == token_t::INVALID)
    {
      excludeToken(token);
    }
    if((type_ == token_t::PUNCT) || (type_ == token_t::DASH))
    {
      excludeToken(token);
    }
    break;
  case token_t::INVALID:
    break;
  }

  if(!token.value_.empty())
  {
    type_ = token.type_;
    last_char_ = token.value_.back();
  }

  return token;
}

