#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class If: public Token
{
  private:
    bool inverseCondition_;
    bool alternativeCondition_;

  public:
    If(const string &value, int lineNumber, bool inverseCondition, bool alternativeCondition);

    const bool &inverseCondition() const;
    bool inverseCondition();
    const bool &alternativeCondition() const;
    bool alternativeCondition();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
