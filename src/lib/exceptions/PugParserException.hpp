#ifndef PugParserException_hpp
#define PugParserException_hpp

#include "../lexer/token/Token.hpp"

#include "PugException.hpp"

namespace pugcpp
{
namespace exceptions
{

using namespace lexer::token;

class PugParserException : public PugException
{
  private:
    static const long serialVersionUID = 2022663314591205451L;

  public:
    PugParserException(
        const string &filename,
        int lineNumber,
        shared_ptr<ITemplateLoader> templateLoader,
        const string &expected,
        const string &got);

    PugParserException(
        const string &filename,
        int lineNumber,
        shared_ptr<ITemplateLoader> templateLoader,
        const Token &token);

    PugParserException(
        const string &filename,
        int lineNumber,
        shared_ptr<ITemplateLoader> templateLoader,
        const string &message);
};
} // namespace exceptions
} // namespace pugcpp
#endif
