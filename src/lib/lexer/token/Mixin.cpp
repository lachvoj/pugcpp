#include "Mixin.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Mixin::Mixin(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Mixin)
{
}

const string &Mixin::getArguments() const
{
    return arguments_;
}
void Mixin::setArguments(const string &arguments)
{
    arguments_ = arguments;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
