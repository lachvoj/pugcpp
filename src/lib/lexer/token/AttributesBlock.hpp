#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class AttributesBlock : Token
{
  public:
    AttributesBlock(const string &value, int lineNumber);
    ~AttributesBlock();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp