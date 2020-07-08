#include "./PugParserException.hpp"

namespace pugcpp
{
namespace exceptions
{
PugParserException::PugParserException(
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader,
    const string &expected,
    const string &got)
: PugException("expected " + expected + "but got " + got, filename, lineNumber, templateLoader, nullptr)
{
}

PugParserException::PugParserException(
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader,
    const Token &token)
: PugException("unknown token " + to_string(token.getType()), filename, lineNumber, templateLoader, nullptr)
{
}

PugParserException::PugParserException(
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader,
    const string &message)
: PugException(message, filename, lineNumber, templateLoader, nullptr)
{
}
} // namespace exceptions
} // namespace pugcpp