#include "If.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
If::If(const string &value, int lineNumber, bool inverseCondition, bool alternativeCondition)
: Token::Token(value, lineNumber, e_If), inverseCondition_(inverseCondition),
  alternativeCondition_(alternativeCondition)
{
}

const bool If::isInverseCondition() const
{
    return inverseCondition_;
}

void If::setInverseCondition(bool inverseCondition)
{
    inverseCondition_ = inverseCondition;
}

const bool If::isAlternativeCondition() const
{
    return alternativeCondition_;
}

void If::setAlternativeCondition(bool alternativeCondition)
{
    alternativeCondition_ = alternativeCondition;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
