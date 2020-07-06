#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Expression: public Token
{
  private:
    bool escape_;

  public:
    Expression(const string &value, int lineNumber, bool escape);

    const bool escape() const;
    bool &escape();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
