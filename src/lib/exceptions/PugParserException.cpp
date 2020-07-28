#include "./PugParserException.hpp"

namespace pugcpp
{
namespace exceptions
{
PugParserException::PugParserException(
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader,
    TokenType expected,
    TokenType got)
: PugException(
      "expected " + Token::getTypeNameFromTokenType(expected) + "but got " + Token::getTypeNameFromTokenType(got),
      filename,
      lineNumber,
      templateLoader,
      nullptr)
{
}

PugParserException::PugParserException(
    const string &filename,
    int lineNumber,
    shared_ptr<ITemplateLoader> templateLoader,
    const Token &token)
: PugException("unknown token " + token.getTypeName(), filename, lineNumber, templateLoader, nullptr)
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