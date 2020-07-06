#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Interpolation: public Token
{
  public:
    Interpolation(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
