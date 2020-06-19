#include "Interpolation.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Interpolation::Interpolation(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Interpolation)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
