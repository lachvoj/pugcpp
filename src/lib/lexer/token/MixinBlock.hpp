#pragma once

#include "Token.hpp"

namespace token
{
class MixinBlock : Token
{
  public:
    MixinBlock(const string &value, int lineNumber);
    ~MixinBlock();
};
} // namespace token
