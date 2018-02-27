#include "format_iterator.h"

#include <algorithm>
#include <stdexcept>

format_iterator::shared_data::shared_data(std::ostream& out, size_t width):
  out_(&out),
  width_(width),
  buf_(0),
  last_token_(buf_.begin())
{
  buf_.reserve(width_);
}

format_iterator::shared_data::~shared_data()
{
  std::copy(buf_.begin(), buf_.end(), std::ostream_iterator<char>(*out_));
  *out_ << '\n';
}

format_iterator::format_iterator(std::ostream &out, size_t width) :
  data_(std::make_shared<format_iterator::shared_data>(out, width))
{}

format_iterator& format_iterator::operator=(const token_t &token)
{
  switch (token.type_)
  {
  case token_t::PUNCT:
    if(data_->buf_.size() + token.value_.size() > data_->width_)
    {
      std::copy(data_->buf_.begin(), data_->last_token_, std::ostream_iterator<char>(*data_->out_));
      *data_->out_ << '\n';
      data_->last_token_ = data_->buf_.erase(data_->buf_.begin(), data_->last_token_);
    }
    data_->buf_.push_back(token.value_.front());
    break;
  case token_t::DASH:
    if(data_->buf_.size() + token.value_.size() + 1 > data_->width_)
    {
      std::copy(data_->buf_.begin(), data_->last_token_, std::ostream_iterator<char>(*data_->out_));
      *data_->out_ << '\n';
      data_->last_token_ = data_->buf_.erase(data_->buf_.begin(), data_->last_token_);
    }
    data_->buf_.push_back(' ');
    data_->buf_.insert(data_->buf_.end(), token.value_.begin(), token.value_.end());
    break;
  case token_t::WORD:
  case token_t::NUMB:
    if(data_->buf_.size() + token.value_.size() + 1 > data_->width_)
    {
      std::copy(data_->buf_.begin(), data_->buf_.end(), std::ostream_iterator<char>(*data_->out_));
      *data_->out_ << '\n';
      data_->buf_.clear();
    }
    else
    {
      if(!data_->buf_.empty())
      {
        data_->buf_.push_back(' ');
      }
    }
    data_->last_token_ = data_->buf_.insert(data_->buf_.end(), token.value_.begin(), token.value_.end());
    break;
  case token_t::INVALID:
    break;
  }

  return *this;
}

format_iterator& format_iterator::operator*()
{
  return *this;
}

format_iterator& format_iterator::operator++()
{
  return *this;
}

format_iterator& format_iterator::operator++(int)
{
  return *this;
}
