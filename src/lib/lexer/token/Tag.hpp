#pragma once

#include "Token.hpp"

namespace token
{
class Tag : Token
{
  public:
    Tag(const string &value, int lineNumber);
    ~Tag();
};
} // namespace token
