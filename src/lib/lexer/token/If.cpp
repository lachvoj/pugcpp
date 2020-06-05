#include "If.hpp"

namespace token
{
If::If(const string &value, int lineNumber, bool inverseCondition = false, bool alternativeCondition = false)
    : Token::Token(value, lineNumber, e_If), inverseCondition_(inverseCondition),
      alternativeCondition_(alternativeCondition)
{
}

const bool &If::inverseCondition() const
{
    return inverseCondition_;
}

bool If::inverseCondition()
{
    return inverseCondition_;
}

const bool &If::alternativeCondition() const
{
    return alternativeCondition_;
}

bool If::alternativeCondition()
{
    return alternativeCondition_;
}
} // namespace token
