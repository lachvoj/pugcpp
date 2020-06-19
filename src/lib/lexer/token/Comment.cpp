#include "Comment.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Comment::Comment(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Comment)
{
}

Comment::Comment(const string &value, int lineNumber, bool buffer) : Token::Token(value, lineNumber, buffer, e_Comment)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
