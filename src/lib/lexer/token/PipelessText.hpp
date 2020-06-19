#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class PipelessText : Token
{
  public:
    PipelessText(const string &value, int lineNumber);
    ~PipelessText();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
