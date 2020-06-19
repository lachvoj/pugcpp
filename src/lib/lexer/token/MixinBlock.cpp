#include "MixinBlock.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
MixinBlock::MixinBlock(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_MixinBlock)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
