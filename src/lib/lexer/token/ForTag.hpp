#pragma once

#include "Token.hpp"

namespace token
{
class ForTag : Token
{
  public:
    ForTag(const string &value, int lineNumber);
    ~ForTag();
};
} // namespace token
