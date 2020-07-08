#include "Outdent.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Outdent::Outdent(int lineNumber) : Token::Token(lineNumber, e_Outdent)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
