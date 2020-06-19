#include "Exception.hpp"

namespace pugcpp
{
namespace exceptions
{
Exception::Exception(const string &error, const std::exception *e)
{
    if (e != nullptr)
        m_clThrowable = *e;
    m_sError = error;
}

Exception::Exception(const string &error)
{
    m_sError = error;
}

const char *Exception::what() const noexcept
{
    return m_sError.c_str();
}

} // namespace exceptions
} // namespace pugcpp