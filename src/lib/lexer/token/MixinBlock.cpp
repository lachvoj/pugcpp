#include "MixinBlock.hpp"

namespace token
{
MixinBlock::MixinBlock(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_MixinBlock)
{
}
} // namespace token
