#pragma once

#include "Token.hpp"

namespace token
{
class UnbufferedComment : Token
{
  public:
    UnbufferedComment(const string &value, int lineNumber);
    ~UnbufferedComment();
};
} // namespace token
