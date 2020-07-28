#include "Call.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Call::Call(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Call)
{
}

void Call::setArguments(const string &arguments)
{
    arguments_ = arguments;
}

const string &Call::getArguments() const
{
    return arguments_;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
