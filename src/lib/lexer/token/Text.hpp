#pragma once

#include "Token.hpp"

namespace token
{
class Text : Token
{
  public:
    Text(const string &value, int lineNumber);
    ~Text();
};
} // namespace token
