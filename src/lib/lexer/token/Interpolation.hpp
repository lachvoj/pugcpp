#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Interpolation : Token
{
  public:
    Interpolation(const string &value, int lineNumber);
    ~Interpolation();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
