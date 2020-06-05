#include "PugCompilerException.hpp"

namespace exceptions
{
PugCompilerException::PugCompilerException(const parserNode::Node &nd, shared_ptr<tmpl::ITemplateLoader> &templateLoader,
                                           const string &message)
    : PugException(message, nd.getFileName(), nd.getLineNumber(), templateLoader)
{
}
} // namespace exceptions