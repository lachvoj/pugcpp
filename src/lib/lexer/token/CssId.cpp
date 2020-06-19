#include "CssId.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
CssId::CssId(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_CssId)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
