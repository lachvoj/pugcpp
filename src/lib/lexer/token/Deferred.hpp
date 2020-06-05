#pragma once

#include "Token.hpp"

namespace token
{
class Deferred : Token
{
  public:
    Deferred(const string &value, int lineNumber);
    ~Deferred();
};
} // namespace token
