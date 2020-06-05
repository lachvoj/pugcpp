#include "Deferred.hpp"

namespace token
{
Deferred::Deferred(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Deferred)
{
}
} // namespace token
