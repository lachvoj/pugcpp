#pragma once

#include "Token.hpp"

namespace token
{
class AttributesBlock : Token
{
  public:
    AttributesBlock(const string &value, int lineNumber);
    ~AttributesBlock();
};
} // namespace token