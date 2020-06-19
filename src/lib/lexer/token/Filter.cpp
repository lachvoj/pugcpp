#include "Filter.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Filter::Filter(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Filter)
{
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
