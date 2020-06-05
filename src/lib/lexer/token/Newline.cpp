#include "Newline.hpp"

namespace token
{
Newline::Newline(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Newline)
{
}
} // namespace token
