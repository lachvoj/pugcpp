#pragma once

#include "Token.hpp"

namespace token
{
class Interpolation : Token
{
  public:
    Interpolation(const string &value, int lineNumber);
    ~Interpolation();
};
} // namespace token