#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class CaseToken : Token
{
  public:
    CaseToken(const string &value, int lineNumber);
    ~CaseToken();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
