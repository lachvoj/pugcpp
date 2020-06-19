#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Doctype : Token
{
  public:
    Doctype(const string &value, int lineNumber);
    ~Doctype();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
