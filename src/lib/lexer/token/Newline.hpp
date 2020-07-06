#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Newline: public Token
{
  public:
    Newline(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
