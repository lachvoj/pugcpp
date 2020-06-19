#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Filter : Token
{
  public:
    Filter(const string &value, int lineNumber);
    ~Filter();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
