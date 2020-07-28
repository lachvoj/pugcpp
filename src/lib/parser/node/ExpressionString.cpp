#include "ExpressionString.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
ExpressionString::ExpressionString(const string &value) : value_(value)
{
}

const string &ExpressionString::getValue() const
{
    return value_;
}

void ExpressionString::setValue(const string &value)
{
    value_ = value;
}

const bool ExpressionString::isEscape() const
{
    return escape_;
}

void ExpressionString::setEscape(bool escape)
{
    escape_ = escape;
}

} // namespace node
} // namespace parser
} // namespace pugcpp