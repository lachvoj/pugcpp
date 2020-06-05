#include "PugException.hpp"

namespace exceptions
{
PugException::PugException(const string &message, const string &filename, int lineNumber,
                           shared_ptr<tmpl::ITemplateLoader> templateLoader)
    : Exception(message), m_sFilename(filename), m_nLineNumber(lineNumber), m_pTemplateLoader(templateLoader)
{
}

PugException::PugException(const string &message) : Exception(message)
{
}

const char *what() const noexcept override
{
    return what().c_str();
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