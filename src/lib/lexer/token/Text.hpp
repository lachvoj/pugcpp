#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Text: public Token
{
  public:
    Text(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
