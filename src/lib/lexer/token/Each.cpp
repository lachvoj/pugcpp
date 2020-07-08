#include "Each.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Each::Each(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Each)
{
}

const string &Each::code() const
{
    return code_;
}

string &Each::code()
{
    return code_;
}

const string &Each::key() const
{
    return key_;
}

string &Each::key()
{
    return key_;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
