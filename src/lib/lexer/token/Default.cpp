#include "Default.hpp"

namespace token
{
Default::Default(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Default)
{
}
} // namespace token
