#include "ExpressionException.hpp"

namespace pugcpp
{
namespace exceptions
{
ExpressionException::ExpressionException(const string &expression)
: Exception("unable to evaluate [" + expression + "]")
{
}

} // namespace exceptions
} // namespace pugcpp