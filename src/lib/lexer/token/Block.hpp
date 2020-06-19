#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Block : Token
{
  public:
    Block(const string &value, int lineNumber);
    ~Block();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp