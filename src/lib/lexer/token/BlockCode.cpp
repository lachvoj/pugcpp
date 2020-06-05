#include "BlockCode.hpp"

namespace token
{
BlockCode::BlockCode(int lineNumber) : Token::Token(lineNumber, e_BlockCode)
{
}
} // namespace token
