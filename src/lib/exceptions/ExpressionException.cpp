#include "ExpressionException.hpp"

namespace exceptions
{

ExpressionException::ExpressionException(const string &expression)
    :Exception("unable to evaluate [" + expression + "]")
{
}

} // namespace exceptions
