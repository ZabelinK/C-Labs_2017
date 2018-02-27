#include "errors.h"

const char* EmptyError::what() const noexcept
{
  return "<EMPTY>";
}


const char* BookMarkError::what() const noexcept
{
  return "<INVALID BOOKMARK>";
}


const char* StepError::what() const noexcept
{
  return "<INVALID STEP>";
}
