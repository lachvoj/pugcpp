#include "Attr.hpp"

namespace parserNode
{

Attr::Attr(const string &name, const any &value, bool escaped) : name_(name), value_(value), escaped_(escaped)
{
}

const string &Attr::getName() const
{
    return name_;
}

any Attr::getValue() const
{
    return value_;
}

bool Attr::isEscaped()
{
    return escaped_;
}

} // namespace parserNode
