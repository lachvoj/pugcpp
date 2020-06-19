#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class CssId : Token
{
  public:
    CssId(const string &value, int lineNumber);
    ~CssId();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
