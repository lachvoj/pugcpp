#pragma once

#include "Token.hpp"

namespace token
{
class Else : Token
{
  public:
    Else(const string &value, int lineNumber);
    ~Else();
};
} // namespace token
