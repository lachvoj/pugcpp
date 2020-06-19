#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class ElseIf : Token
{
  public:
    ElseIf(const string &value, int lineNumber);
    ~ElseIf();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
