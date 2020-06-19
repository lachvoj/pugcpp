#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Else : Token
{
  public:
    Else(const string &value, int lineNumber);
    ~Else();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
