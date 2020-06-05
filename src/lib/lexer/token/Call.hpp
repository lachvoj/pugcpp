#pragma once

#include "Token.hpp"

namespace token
{
class Call : Token
{
  private:
    string arguments_;

  public:
    Call(const string &value, int lineNumber);
    ~Call();

    string &arguments();
    const string &arguments() const;
};
} // namespace token
