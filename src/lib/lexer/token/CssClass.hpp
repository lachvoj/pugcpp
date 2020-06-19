#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class CssClass : Token
{
  public:
    CssClass(const string &value, int lineNumber);
    ~CssClass();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
