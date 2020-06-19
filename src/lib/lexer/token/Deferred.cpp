#include "Deferred.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Deferred::Deferred(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Deferred)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
