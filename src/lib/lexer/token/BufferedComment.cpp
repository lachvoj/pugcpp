#include "BufferedComment.hpp"

namespace token
{
BufferedComment::BufferedComment(const string &value, int lineNumber)
    : Token::Token(value, lineNumber, e_BufferedComment)
{
}
} // namespace token
