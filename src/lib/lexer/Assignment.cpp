#include "Assignment.hpp"

namespace pugcpp
{
namespace lexer
{
Assignment::Assignment(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Assignment)
{
}
} // namespace lexer
} // namespace pugcpp
