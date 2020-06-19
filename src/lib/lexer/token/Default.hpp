#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Default : Token
{
  public:
    Default(const string &value, int lineNumber);
    ~Default();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
