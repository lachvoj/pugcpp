#pragma once

#include "token/Token.hpp"

namespace pugcpp
{
namespace lexer
{
using namespace token;

class Assignment : Token
{
  public:
    Assignment(const string &value, int lineNumber);
};
} // namespace lexer
} // namespace pugcpp
