#include "EndPugInterpolation.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
EndPugInterpolation::EndPugInterpolation(const string &value, int lineNumber)
: Token::Token(value, lineNumber, e_EndPugInterpolation)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
