#include "Assignment.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Assignment::Assignment(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Assignment)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
