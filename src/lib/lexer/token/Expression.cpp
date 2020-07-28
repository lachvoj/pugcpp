#include "Expression.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Expression::Expression(const string &value, int lineNumber, bool escape)
: Token::Token(value, lineNumber, e_Expression), escape_(escape)
{
}

const bool Expression::isEscape() const
{
    return escape_;
}

void Expression::setEscape(bool escape)
{
    escape_ = escape;
}

} // namespace token
} // namespace lexer
} // namespace pugcpp