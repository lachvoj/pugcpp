#include "While.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
While::While(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_While)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
