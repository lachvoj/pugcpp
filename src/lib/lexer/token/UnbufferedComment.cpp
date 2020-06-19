#include "UnbufferedComment.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
UnbufferedComment::UnbufferedComment(const string &value, int lineNumber)
: Token::Token(value, lineNumber, e_UnbufferedComment)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
