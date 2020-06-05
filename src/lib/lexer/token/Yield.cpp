#include "Yield.hpp"

namespace token
{
Yield::Yield(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Yield)
{
}
} // namespace token
