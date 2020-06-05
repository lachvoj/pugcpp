#include "AttributesBlock.hpp"

namespace token
{
AttributesBlock::AttributesBlock(const string &value, int lineNumber)
    : Token::Token(value, lineNumber, e_AttributeBlock)
{
}
} // namespace token