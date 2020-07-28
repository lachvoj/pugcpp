#include "Attr.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
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

const bool Attr::isEscaped() const
{
    return escaped_;
}

} // namespace node
} // namespace parser
} // namespace pugcpp
