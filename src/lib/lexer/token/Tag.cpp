#include "Tag.hpp"

namespace token
{
Tag::Tag(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Tag)
{
}
} // namespace token
