#pragma once

#include "Token.hpp"

namespace token
{
class Expression : Token
{
  private:
    bool escape_;

  public:
    Expression(const string &value, int lineNumber, bool escape);
    ~Expression();

    const bool escape() const;
    bool &escape();
};
} // namespace token
