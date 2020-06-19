#include "When.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
When::When(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_When)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
