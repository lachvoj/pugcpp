#include "AttributesBlock.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
AttributesBlock::AttributesBlock(const string &value, int lineNumber)
: Token::Token(value, lineNumber, e_AttributesBlock)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp