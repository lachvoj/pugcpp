#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class ForTag : Token
{
  public:
    ForTag(const string &value, int lineNumber);
    ~ForTag();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
