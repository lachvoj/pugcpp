#include "Eos.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Eos::Eos(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Eos)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
