#pragma once

#include "Token.hpp"

namespace token
{
class Eos : Token
{
  public:
    Eos(const string &value, int lineNumber);
    ~Eos();
};
} // namespace token
