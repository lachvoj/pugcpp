#pragma once

#include "Token.hpp"

namespace token
{
class CaseToken : Token
{
  public:
    CaseToken(const string &value, int lineNumber);
    ~CaseToken();
};
} // namespace token
