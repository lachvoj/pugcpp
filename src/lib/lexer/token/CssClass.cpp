#include "CssClass.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
CssClass::CssClass(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_CssClass)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
