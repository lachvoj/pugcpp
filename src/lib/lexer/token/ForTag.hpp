#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class ForTag: public Token
{
  public:
    ForTag(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
