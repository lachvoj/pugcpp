#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Eos : Token
{
  public:
    Eos(const string &value, int lineNumber);
    ~Eos();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
