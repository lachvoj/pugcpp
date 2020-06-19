#include "Indent.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Indent::Indent(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Indent)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
