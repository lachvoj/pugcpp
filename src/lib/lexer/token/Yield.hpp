#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Yield: public Token
{
  public:
    Yield(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
