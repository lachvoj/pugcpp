#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Newline : Token
{
  public:
    Newline(const string &value, int lineNumber);
    ~Newline();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
