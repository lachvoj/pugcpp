#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class MixinBlock : Token
{
  public:
    MixinBlock(const string &value, int lineNumber);
    ~MixinBlock();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
