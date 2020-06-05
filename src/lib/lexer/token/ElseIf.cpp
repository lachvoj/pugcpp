#include "ElseIf.hpp"

namespace token
{
ElseIf::ElseIf(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_ElseIf)
{
}
} // namespace token
