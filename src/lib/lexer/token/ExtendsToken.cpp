#include "ExtendsToken.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
ExtendsToken::ExtendsToken(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_ExtendsToken)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
