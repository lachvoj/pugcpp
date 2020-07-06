#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Outdent: public Token
{
  public:
    Outdent(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
