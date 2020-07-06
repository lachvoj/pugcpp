#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Block: public Token
{
  public:
    Block(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp