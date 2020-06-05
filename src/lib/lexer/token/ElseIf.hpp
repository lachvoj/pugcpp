#pragma once

#include "Token.hpp"

namespace token
{
class ElseIf : Token
{
  public:
    ElseIf(const string &value, int lineNumber);
    ~ElseIf();
};
} // namespace token
