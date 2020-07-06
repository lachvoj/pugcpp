#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Else: public Token
{
  public:
    Else(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
