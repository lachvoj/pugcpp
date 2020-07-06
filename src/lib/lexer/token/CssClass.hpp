#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class CssClass: public Token
{
  public:
    CssClass(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
