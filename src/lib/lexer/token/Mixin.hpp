#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Mixin : Token
{
  private:
    string arguments_;

  public:
    Mixin(const string &value, int lineNumber);
    ~Mixin();

    const string &arguments() const;
    string &arguments();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
