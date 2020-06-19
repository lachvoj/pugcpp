#include "Tag.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Tag::Tag(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Tag)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
