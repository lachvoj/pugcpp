#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class CssId: public Token
{
  public:
    CssId(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
