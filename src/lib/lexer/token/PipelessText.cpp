#include "PipelessText.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
PipelessText::PipelessText(int lineNumber) : Token::Token(lineNumber, e_PipelessText)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
