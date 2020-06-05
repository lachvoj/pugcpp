#include "Else.hpp"

namespace token
{
Else::Else(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Else)
{
}
} // namespace token
