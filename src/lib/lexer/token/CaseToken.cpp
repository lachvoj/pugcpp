#include "CaseToken.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
CaseToken::CaseToken(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_CaseToken)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
