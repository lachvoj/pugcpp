#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Indent : Token
{
  public:
    Indent(const string &value, int lineNumber);
    ~Indent();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
