#pragma once

#include "Token.hpp"

namespace token
{
class CssId : Token
{
  public:
    CssId(const string &value, int lineNumber);
    ~CssId();
};
} // namespace token
