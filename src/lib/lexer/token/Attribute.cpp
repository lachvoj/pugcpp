#include "Attribute.hpp"

namespace token
{
Attribute::Attribute(const string &name, const any &value, bool escape) : name_(name), value_(value), escaped_(escape)
{
}

const string &Attribute::name() const
{
    return name_;
}
const any &Attribute::value() const
{
    return value_;
}
const bool Attribute::escaped() const
{
    return escaped_;
}
} // namespace token