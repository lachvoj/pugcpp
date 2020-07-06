#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class CaseToken: public Token
{
  public:
    CaseToken(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
