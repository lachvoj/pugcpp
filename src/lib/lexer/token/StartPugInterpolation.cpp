#include "StartPugInterpolation.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
StartPugInterpolation::StartPugInterpolation(const string &value, int lineNumber)
: Token::Token(value, lineNumber, e_StartPugInterpolation)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
