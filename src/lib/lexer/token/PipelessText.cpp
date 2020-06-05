#include "PipelessText.hpp"

namespace token
{
PipelessText::PipelessText(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_PipelessText)
{
}
} // namespace token
