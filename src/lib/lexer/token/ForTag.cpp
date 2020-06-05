#include "ForTag.hpp"

namespace token
{
ForTag::ForTag(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_ForTag)
{
}
} // namespace token
