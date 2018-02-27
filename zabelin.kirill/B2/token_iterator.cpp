#include "token_iterator.h"

#include <stdexcept>
#include <locale>
#include <iostream>


token_iterator::shared_data::shared_data():
  iter_value_(),
  in_(nullptr),
  locale_(),
  ok_(false)
{}

token_iterator::shared_data::shared_data(std::istream & in):
  iter_value_(),
  in_(&in),
  locale_(in.getloc()),
  ok_(in)
{}

token_iterator::token_iterator():
  data_(std::make_shared<shared_data>())
{}

token_iterator::token_iterator(std::istream & in):
  data_(std::make_shared<shared_data>(in))
{
  token_iterator::readToken();
}

bool token_iterator::operator==(const token_iterator & it) const
{
  return (data_->ok_ == it.data_->ok_) && (!data_->ok_ || data_->in_ == it.data_->in_);
}

bool token_iterator::operator!=(const token_iterator & it) const
{
  return !(*this == it);
}

token_iterator& token_iterator::operator++()
{
  token_iterator::readToken();
  return *this;
}

token_iterator token_iterator::operator++(int)
{
  token_iterator tmp(*this);
  token_iterator::readToken();
  return tmp;
}

const token_t& token_iterator::operator*() const noexcept
{
  return data_->iter_value_;
}

const token_t* token_iterator::operator->() const noexcept
{
  return &data_->iter_value_;
}

void token_iterator::readToken()
{
  data_->iter_value_ = {token_t::INVALID,
      "",
      data_->iter_value_.line_,
      data_->iter_value_.column_};

  char c = token_iterator::readChar();

  while(std::isspace(c, data_->locale_))
  {
    c = token_iterator::readChar();
  }

  if(c == '-')
  {
    do {
      data_->iter_value_.value_.push_back(c);
      c = token_iterator::readChar();
    } while(c == '-');
    data_->in_->unget();
    if(data_->iter_value_.value_.size() == 1)
    {
      token_iterator::readNumb();
    }
    else
    {
      data_->iter_value_.type_ = token_t::DASH;
    }
  }
  else if(c == '+')
  {
    data_->iter_value_.value_.push_back(c);
    token_iterator::readNumb();
  }
  else if(std::ispunct(c, data_->locale_))
  {
    data_->iter_value_.value_.push_back(c);
    data_->iter_value_.type_ = token_t::PUNCT;
  }
  else if(std::isdigit(c, data_->locale_))
  {
    data_->in_->unget();
    token_iterator::readNumb();
  }
  else if(std::isalpha(c, data_->locale_))
  {
    do {
      data_->iter_value_.value_.push_back(c);
      if((data_->in_->peek() == '-') && (data_->iter_value_.value_.back() == '-'))
      {
        data_->iter_value_.value_.pop_back();
        break;
      }
      c = token_iterator::readChar();
    } while(std::isalpha(c, data_->locale_) || (c == '-'));
    data_->in_->unget();
    data_->iter_value_.type_ = token_t::WORD;
  }
}

void token_iterator::readNumb()
{
  char c = token_iterator::readChar(),
      decimal_point = std::use_facet<std::numpunct<char>>(data_->locale_).decimal_point();

  if(!std::isdigit(c, data_->locale_))
  {
    excludeToken(data_->iter_value_);
  }

  do {
    if((c == decimal_point) && (data_->iter_value_.value_.find(c) != std::string::npos))
    {
      break;
    }

    data_->iter_value_.value_.push_back(c);
    c = token_iterator::readChar();
  } while(std::isdigit(c, data_->locale_) || (c == decimal_point));

  data_->in_->unget();
  data_->iter_value_.type_ = token_t::NUMB;
}

char token_iterator::readChar()
{
  char c = '\0';
  data_->ok_ = (data_->in_ && *data_->in_);
  if(data_->ok_)
  {
    c = data_->in_->get();
    if(c == '\n')
    {
      ++data_->iter_value_.line_;
      data_->iter_value_.column_ = 0;
    }
    else
    {
      ++data_->iter_value_.column_;
    }
  }
  return c;
}
