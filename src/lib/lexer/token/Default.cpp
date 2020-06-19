#include "Default.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Default::Default(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Default)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
