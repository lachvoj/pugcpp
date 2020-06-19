#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Colon : Token
{
  public:
    Colon(int lineNumber);
    ~Colon();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp