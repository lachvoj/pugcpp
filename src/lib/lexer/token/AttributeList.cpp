#include "AttributeList.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
AttributeList::AttributeList(int lineNumber) : Token::Token(lineNumber, e_AttributeList)
{
}

const vector<Attribute> &AttributeList::getAttributes() const
{
    return attributes_;
}

void AttributeList::addAttribute(const string &name, const string &value, bool escapedAttr)
{
    attributes_.push_back(Attribute(name, value, escapedAttr));
}

void AttributeList::addExpressionAttribute(const string &name, const string &expression, bool escapedAttr)
{
    ExpressionString es(expression);
    es.setEscape(escapedAttr);
    any value = es;
    attributes_.push_back(Attribute(name, value, escapedAttr));
}

void AttributeList::addBoolAttribute(const string &name, bool value)
{
    attributes_.push_back(Attribute(name, value, false));
}

} // namespace token
} // namespace lexer
} // namespace pugcpp