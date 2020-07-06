#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Eos: public Token
{
  public:
    Eos(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
