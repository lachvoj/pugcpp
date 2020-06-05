#pragma once

#include "Token.hpp"

namespace token
{
class Yield : Token
{
  public:
    Yield(const string &value, int lineNumber);
    ~Yield();
};
} // namespace token
