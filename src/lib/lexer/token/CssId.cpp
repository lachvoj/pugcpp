#include "CssId.hpp"

namespace token
{
CssId::CssId(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_CssId)
{
}
} // namespace token
