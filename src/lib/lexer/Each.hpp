#pragma once

#include "token/Token.hpp"

namespace token
{
class Each : Token
{
  private:
    string code_;
    string key_;

  public:
    Each(const string &value, int lineNumber);
    ~Each();

    const string &code() const;
    string &code();
    const string &key() const;
    string &key();
};
} // namespace token
