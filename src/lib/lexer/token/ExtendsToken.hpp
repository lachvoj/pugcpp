#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class ExtendsToken : Token
{
  public:
    ExtendsToken(const string &value, int lineNumber);
    ~ExtendsToken();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
