#include "When.hpp"

namespace token
{
When::When(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_When)
{
}
} // namespace token
