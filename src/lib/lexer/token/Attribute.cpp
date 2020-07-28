#include "Attribute.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Attribute::Attribute(const string &name, const any &value, bool escape)
: name_(name), value_(value), escaped_(escape)
{
}

const string &Attribute::getName() const
{
    return name_;
}

const any &Attribute::getValue() const
{
    return value_;
}

const bool Attribute::isEscaped() const
{
    return escaped_;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp