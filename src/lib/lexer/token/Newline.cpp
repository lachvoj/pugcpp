#include "Newline.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Newline::Newline(int lineNumber) : Token::Token(lineNumber, e_Newline)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
