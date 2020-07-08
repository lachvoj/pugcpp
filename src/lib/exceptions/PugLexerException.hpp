#ifndef PugLexerException_hpp
#define PugLexerException_hpp

#include "../template/ITemplateLoader.hpp"

#include "PugException.hpp"

namespace pugcpp
{
namespace exceptions
{
class PugLexerException : public PugException
{
  private:
    static const long serialVersionUID = -4390591022593362563L;

  public:
    PugLexerException(
        const string &message,
        const string &filename,
        int lineNumber,
        shared_ptr<tmpl::ITemplateLoader> templateLoader);
};
} // namespace exceptions
} // namespace pugcpp
#endif
