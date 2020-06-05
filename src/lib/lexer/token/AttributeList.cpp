#include "AttributeList.hpp"

namespace token
{
AttributeList::AttributeList(int lineNumber) : Token::Token(lineNumber, e_AttributeList)
{
}

AttributeList::~AttributeList()
{
}

const list<Attribute> &AttributeList::attributes() const
{
    return attributes_;
}

void AttributeList::addAttribute(const string &name, const string &value, bool escapedAttr)
{
    attributes_.push_back(Attribute(name, value, escapedAttr));
}

void AttributeList::addExpressionAttribute(const string &name, const string &expression, bool escapedAttr)
{
    // TODO: implement this
}

void AttributeList::addBoolAttribute(const string &name, bool value)
{
    attributes_.push_back(Attribute(name, value, false));
}

} // namespace token