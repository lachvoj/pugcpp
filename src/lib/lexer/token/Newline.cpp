#include "Newline.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Newline::Newline(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Newline)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
