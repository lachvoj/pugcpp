#include "Doctype.hpp"

namespace token
{
Doctype::Doctype(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Doctype)
{
}
} // namespace token
