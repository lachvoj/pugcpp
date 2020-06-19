#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class When : Token
{
  public:
    When(const string &value, int lineNumber);
    ~When();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
