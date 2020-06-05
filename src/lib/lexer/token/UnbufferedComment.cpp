#include "UnbufferedComment.hpp"

namespace token
{
UnbufferedComment::UnbufferedComment(const string &value, int lineNumber)
    : Token::Token(value, lineNumber, e_UnbufferedComment)
{
}
} // namespace token
