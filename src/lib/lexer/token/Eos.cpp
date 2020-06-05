#include "Eos.hpp"

namespace token
{
Eos::Eos(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Eos)
{
}
} // namespace token
