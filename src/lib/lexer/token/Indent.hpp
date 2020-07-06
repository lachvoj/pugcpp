#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Indent: public Token
{
  public:
    Indent(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
