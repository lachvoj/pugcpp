#include "ExtendsToken.hpp"

namespace token
{
ExtendsToken::ExtendsToken(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_ExtendsToken)
{
}
} // namespace token
