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
    std::exception *e)
: Exception(message, e), fileName_(filename), lineNumber_(lineNumber), templateLoader_(templateLoader)
{
    sPugExceptionError_ = "\nFile name: " + fileName_;
    sPugExceptionError_ += "\nLine number: " + to_string(lineNumber_);
    sPugExceptionError_ +=  "\n" + error_;
}

PugException::PugException(const string &message) : Exception(message)
{
}

const char *PugException::what() const noexcept
{
    if (!fileName_.empty() && lineNumber_ > -1)
        return sPugExceptionError_.c_str();

    return error_.c_str();

}

const string &PugException::getFilename()
{
    return fileName_;
}

int PugException::getLineNumber()
{
    return lineNumber_;
}
} // namespace exceptions
} // namespace pugcpp
