#pragma once

#include "Token.hpp"

namespace token
{
class If : Token
{
  private:
    bool inverseCondition_;
    bool alternativeCondition_;

  public:
    If(const string &value, int lineNumber, bool inverseCondition, bool alternativeCondition);
    ~If();

    const bool &inverseCondition() const;
    bool inverseCondition();
    const bool &alternativeCondition() const;
    bool alternativeCondition();
};
} // namespace token