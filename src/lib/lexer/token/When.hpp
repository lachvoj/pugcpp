#pragma once

#include "Token.hpp"

namespace token
{
class When : Token
{
  public:
    When(const string &value, int lineNumber);
    ~When();
};
} // namespace token
