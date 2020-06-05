#include "CaseToken.hpp"

namespace token
{
CaseToken::CaseToken(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_CaseToken)
{
}
} // namespace token
