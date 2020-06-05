#include "Mixin.hpp"

namespace token
{
Mixin::Mixin(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Mixin)
{
}

const string &Mixin::arguments() const
{
    return arguments_;
}
string &Mixin::arguments()
{
    return arguments_;
}
} // namespace token
