#include "Yield.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Yield::Yield(int lineNumber) : Token::Token(lineNumber, e_Yield)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
