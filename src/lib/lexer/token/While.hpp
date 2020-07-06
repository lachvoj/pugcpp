#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class While: public Token
{
  public:
    While(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
