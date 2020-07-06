#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Mixin: public Token
{
  private:
    string arguments_;

  public:
    Mixin(const string &value, int lineNumber);

    const string &arguments() const;
    string &arguments();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
