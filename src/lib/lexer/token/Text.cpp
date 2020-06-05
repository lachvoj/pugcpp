#include "Text.hpp"

namespace token
{
Text::Text(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Text)
{
}
} // namespace token
