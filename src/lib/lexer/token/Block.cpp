#include "Block.hpp"

namespace token
{
Block::Block(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Block)
{
}
} // namespace token