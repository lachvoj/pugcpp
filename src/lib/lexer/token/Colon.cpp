#include "Colon.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Colon::Colon(int lineNumber) : Token::Token(lineNumber, e_Colon)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
