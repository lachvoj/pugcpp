#include "PipelessText.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
PipelessText::PipelessText(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_PipelessText)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
