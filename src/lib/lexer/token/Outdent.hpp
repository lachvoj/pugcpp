#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Outdent : Token
{
  public:
    Outdent(const string &value, int lineNumber);
    ~Outdent();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
