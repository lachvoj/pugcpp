#include "./PugLexerException.hpp"

namespace pugcpp
{
namespace exceptions
{
PugLexerException::PugLexerException(
    const string &message,
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader)
: PugException(message, filename, lineNumber, templateLoader, nullptr)
{
}
} // namespace exceptions
} // namespace pugcpp