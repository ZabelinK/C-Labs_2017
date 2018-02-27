#include "token_t.h"

#include <stdexcept>

void excludeToken(const token_t & err_token)
{
  throw std::invalid_argument("Wrong input data line: " + std::to_string(err_token.line_)
      + " column: " + std::to_string(err_token.column_));
}
