#include "Assignment.hpp"

namespace token
{
Assignment::Assignment(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Assignment)
{
}
} // namespace token
