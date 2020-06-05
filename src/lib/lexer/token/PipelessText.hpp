#pragma once

#include "Token.hpp"

namespace token
{
class PipelessText : Token
{
  public:
    PipelessText(const string &value, int lineNumber);
    ~PipelessText();
};
} // namespace token
