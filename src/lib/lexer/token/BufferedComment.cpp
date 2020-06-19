#include "BufferedComment.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
BufferedComment::BufferedComment(const string &value, int lineNumber)
: Token::Token(value, lineNumber, e_BufferedComment)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
