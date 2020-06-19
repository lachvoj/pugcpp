#include "BlockCode.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
BlockCode::BlockCode(int lineNumber) : Token::Token(lineNumber, e_BlockCode)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
