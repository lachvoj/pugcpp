#include "Else.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Else::Else(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Else)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
