#pragma once

#include "token/Token.hpp"

namespace token
{
class Assignment : Token
{
  public:
    Assignment(const string &value, int lineNumber);
    ~Assignment();
};
} // namespace token
