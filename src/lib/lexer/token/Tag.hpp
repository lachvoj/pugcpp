#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Tag : Token
{
  public:
    Tag(const string &value, int lineNumber);
    ~Tag();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
