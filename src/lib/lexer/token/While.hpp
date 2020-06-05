#pragma once

#include "Token.hpp"

namespace token
{
class While : Token
{
  public:
    While(const string &value, int lineNumber);
    ~While();
};
} // namespace token
