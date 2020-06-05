#pragma once

#include "Token.hpp"

namespace token
{
class Block : Token
{
  public:
    Block(const string &value, int lineNumber);
    ~Block();
};
} // namespace token