#include "CssClass.hpp"

namespace token
{
CssClass::CssClass(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_CssClass)
{
}
} // namespace token
