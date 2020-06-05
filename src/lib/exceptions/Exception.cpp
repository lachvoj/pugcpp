#include "Exception.hpp"

namespace exceptions
{
Exception::Exception(const string &error)
{
    m_sError = error;
}

const char *Exception::what() const noexcept
{
    return m_sError.c_str();
}

} // namespace exceptions