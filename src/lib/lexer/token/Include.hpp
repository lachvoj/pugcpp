#pragma once

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Include : Token
{
  private:
    string filter_;
    Token attrs_;

  public:
    Include(const string &value, int lineNumber);
    ~Include();

    const string &filter() const;
    string &filter();
    const Token &attrs() const;
    Token &attrs();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
