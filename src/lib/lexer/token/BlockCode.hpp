#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class BlockCode : Token
{
  public:
    BlockCode(int lineNumber);
    ~BlockCode();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp