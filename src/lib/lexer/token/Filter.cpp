#include "Filter.hpp"

namespace token
{
Filter::Filter(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Filter)
{
}
} // namespace token
