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

const string &Include::getFilter() const
{
    return filter_;
}

void Include::setFilter(const string &filter)
{
    filter_ = filter;
}

shared_ptr<Token> Include::getAttrs()
{
    return attrs_;
}

void Include::setAttrs(shared_ptr<Token> attrs)
{
    attrs_ = attrs;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
