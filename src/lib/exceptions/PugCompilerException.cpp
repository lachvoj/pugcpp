#include "PugCompilerException.hpp"

namespace pugcpp
{
namespace exceptions
{
PugCompilerException::PugCompilerException(
    const Node &nd,
    shared_ptr<ITemplateLoader> templateLoader,
    std::exception *e)
: PugException((e != nullptr) ? string(e->what()) : "", nd.getFileName(), nd.getLineNumber(), templateLoader, e)
{
}
PugCompilerException::PugCompilerException(
    const Node &nd,
    shared_ptr<ITemplateLoader> templateLoader,
    const string &message)
: PugException(message, nd.getFileName(), nd.getLineNumber(), templateLoader, nullptr)
{
}
} // namespace exceptions
} // namespace pugcpp
