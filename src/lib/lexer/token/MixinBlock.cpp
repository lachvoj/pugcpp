#include "MixinBlock.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
MixinBlock::MixinBlock(int lineNumber) : Token::Token(lineNumber, e_MixinBlock)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
