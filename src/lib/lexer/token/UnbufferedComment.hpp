#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class UnbufferedComment : Token
{
  public:
    UnbufferedComment(const string &value, int lineNumber);
    ~UnbufferedComment();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
