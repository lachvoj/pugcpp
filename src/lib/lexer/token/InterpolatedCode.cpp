#include "InterpolatedCode.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
InterpolatedCode::InterpolatedCode(const string &value, int lineNumber)
: Token::Token(value, lineNumber, e_InterpolatedCode)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
