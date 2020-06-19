#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Deferred : Token
{
  public:
    Deferred(const string &value, int lineNumber);
    ~Deferred();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
