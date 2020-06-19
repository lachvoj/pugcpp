#include "Yield.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Yield::Yield(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Yield)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
