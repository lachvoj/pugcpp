#include "While.hpp"

namespace token
{
While::While(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_While)
{
}
} // namespace token
