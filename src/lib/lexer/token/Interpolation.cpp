#include "Interpolation.hpp"

namespace token
{
Interpolation::Interpolation(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Interpolation)
{
}
} // namespace token
