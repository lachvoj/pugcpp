#include "TextHtml.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
TextHtml::TextHtml(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_TextHtml)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
