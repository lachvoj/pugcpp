#include "Include.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Include::Include(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Include)
{
}

const string &Include::filter() const
{
    return filter_;
}

string &Include::filter()
{
    return filter_;
}

const Token &Include::attrs() const
{
    return attrs_;
}

Token &Include::attrs()
{
    return attrs_;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
