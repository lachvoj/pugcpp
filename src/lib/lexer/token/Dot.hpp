#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Dot : Token
{
  public:
    Dot(int lineNumber);
    ~Dot();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
