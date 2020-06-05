#pragma once

#include "Token.hpp"

namespace token
{
class BufferedComment : Token
{
  public:
    BufferedComment(const string &value, int lineNumber);
    ~BufferedComment();
};
} // namespace token