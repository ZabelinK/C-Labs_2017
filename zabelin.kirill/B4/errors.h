#ifndef PHONEBOOKERROR_H
#define PHONEBOOKERROR_H

#include <exception>

class PhoneBookError : public std::exception
{
public:
  virtual ~PhoneBookError() = default;
  virtual const char* what() const noexcept override = 0;
};

class MarkError : public std::exception
{
public:
  virtual ~MarkError() = default;
  virtual const char* what() const noexcept override = 0;
};

class EmptyError : public PhoneBookError
{
  const char* what() const noexcept override;
};

class BookMarkError : public MarkError
{
  const char* what() const noexcept override;
};

class StepError : public MarkError
{
  const char* what() const noexcept override;
};

#endif // PHONEBOOKERROR_H
