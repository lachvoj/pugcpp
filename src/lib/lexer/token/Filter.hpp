#pragma once

#include "Token.hpp"

namespace token
{
class Filter : Token
{
  public:
    Filter(const string &value, int lineNumber);
    ~Filter();
};
} // namespace token
