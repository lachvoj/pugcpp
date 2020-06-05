#pragma once

#include "Token.hpp"

namespace token
{
class BlockCode : Token
{
  public:
    BlockCode(int lineNumber);
    ~BlockCode();
};
} // namespace token