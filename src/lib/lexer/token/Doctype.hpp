#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Doctype: public Token
{
  public:
    Doctype(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
