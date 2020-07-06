#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Filter: public Token
{
  public:
    Filter(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
