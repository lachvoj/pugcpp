#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Comment : Token
{
  public:
    Comment(const string &value, int lineNumber);
    Comment(const string &value, int lineNumber, bool buffer);
    ~Comment();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
