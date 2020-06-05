#pragma once

#include "Token.hpp"

namespace token
{
class Outdent : Token
{
  public:
    Outdent(const string &value, int lineNumber);
    ~Outdent();
};
} // namespace token
