#pragma once

#include "Token.hpp"

namespace token
{
class Doctype : Token
{
  public:
    Doctype(const string &value, int lineNumber);
    ~Doctype();
};
} // namespace token
