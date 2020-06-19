#include "Expression.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Expression::Expression(const string &value, int lineNumber, bool escape = false)
: Token::Token(value, lineNumber, e_Expression), escape_(escape)
{
}

const bool Expression::escape() const
{
    return escape_;
}

bool &Expression::escape()
{
    return escape_;
}

} // namespace token
} // namespace lexer
} // namespace pugcpp