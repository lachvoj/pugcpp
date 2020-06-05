#pragma once

#include "Token.hpp"

namespace token
{
class Newline : Token
{
  public:
    Newline(const string &value, int lineNumber);
    ~Newline();
};
} // namespace token
