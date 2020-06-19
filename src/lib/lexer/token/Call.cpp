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

string &Call::arguments()
{
    return arguments_;
}

const string &Call::arguments() const
{
    return arguments_;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
