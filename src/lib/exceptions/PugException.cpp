#include "PugException.hpp"

namespace pugcpp
{
namespace exceptions
{
PugException::PugException(
    const string &message,
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader,
    const std::exception *e)
: Exception(message, e), m_sFilename(filename), m_nLineNumber(lineNumber), m_pTemplateLoader(templateLoader)
{
}

PugException::PugException(const string &message) : Exception(message)
{
}

const char *PugException::what() const noexcept
{
    return m_sError.c_str();
}

const string &PugException::getFilename()
{
    return m_sFilename;
}

int PugException::getLienNumber()
{
    return m_nLineNumber;
}
} // namespace exceptions
} // namespace pugcpp
