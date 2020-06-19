#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Yield : Token
{
  public:
    Yield(const string &value, int lineNumber);
    ~Yield();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
