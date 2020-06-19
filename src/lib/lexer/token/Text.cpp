#include "Text.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Text::Text(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Text)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
