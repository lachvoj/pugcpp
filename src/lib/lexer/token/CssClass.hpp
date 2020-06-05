#pragma once

#include "Token.hpp"

namespace token
{
class CssClass : Token
{
  public:
    CssClass(const string &value, int lineNumber);
    ~CssClass();
};
} // namespace token
