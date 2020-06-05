#pragma once

#include "Token.hpp"

namespace token
{
class Dot : Token
{
  public:
    Dot(int lineNumber);
    ~Dot();
};
} // namespace token
