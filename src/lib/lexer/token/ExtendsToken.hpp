#pragma once

#include "Token.hpp"

namespace token
{
class ExtendsToken : Token
{
  public:
    ExtendsToken(const string &value, int lineNumber);
    ~ExtendsToken();
};
} // namespace token
