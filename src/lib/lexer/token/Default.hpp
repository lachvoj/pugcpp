#pragma once

#include "Token.hpp"

namespace token
{
class Default : Token
{
  public:
    Default(const string &value, int lineNumber);
    ~Default();
};
} // namespace token
