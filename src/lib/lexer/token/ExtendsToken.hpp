#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class ExtendsToken: public Token
{
  public:
    ExtendsToken(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
