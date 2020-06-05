#pragma once

#include "Token.hpp"

namespace token
{
class Colon : Token
{
  public:
    Colon(int lineNumber);
    ~Colon();
};
} // namespace token