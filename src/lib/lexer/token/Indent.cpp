#include "Indent.hpp"

namespace token
{
Indent::Indent(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Indent)
{
}
} // namespace token
