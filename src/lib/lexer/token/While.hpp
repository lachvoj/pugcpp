#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class While : Token
{
  public:
    While(const string &value, int lineNumber);
    ~While();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
