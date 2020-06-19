#include "ElseIf.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
ElseIf::ElseIf(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_ElseIf)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
