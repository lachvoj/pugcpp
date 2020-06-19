#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Text : Token
{
  public:
    Text(const string &value, int lineNumber);
    ~Text();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
