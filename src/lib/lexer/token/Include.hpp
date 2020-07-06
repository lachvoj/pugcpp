#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Include: public Token
{
  private:
    string filter_;
    Token attrs_;

  public:
    Include(const string &value, int lineNumber);

    const string &filter() const;
    string &filter();
    const Token &attrs() const;
    Token &attrs();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
