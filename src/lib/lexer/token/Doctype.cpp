#include "Doctype.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Doctype::Doctype(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Doctype)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
