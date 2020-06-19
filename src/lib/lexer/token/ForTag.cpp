#include "ForTag.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
ForTag::ForTag(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_ForTag)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
