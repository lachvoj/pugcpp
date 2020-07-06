#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Comment: public Token
{
  public:
    Comment(const string &value, int lineNumber);
    Comment(const string &value, int lineNumber, bool buffer);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
