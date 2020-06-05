#include "Outdent.hpp"

namespace token
{
Outdent::Outdent(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Outdent)
{
}
} // namespace token
