#include "Block.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Block::Block(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Block)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp