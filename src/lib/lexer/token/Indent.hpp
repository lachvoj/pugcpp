#pragma once

#include "Token.hpp"

namespace token
{
class Indent : Token
{
  public:
    Indent(const string &value, int lineNumber);
    ~Indent();
};
} // namespace token
