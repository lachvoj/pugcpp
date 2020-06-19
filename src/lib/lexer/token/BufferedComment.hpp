#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class BufferedComment : Token
{
  public:
    BufferedComment(const string &value, int lineNumber);
    ~BufferedComment();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp