#include "Outdent.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Outdent::Outdent(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Outdent)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
