#ifndef PugCompilerException_hpp
#define PugCompilerException_hpp

#include <memory>
#include <string>

#include "../parser/node/Node.hpp"
#include "../template/ITemplateLoader.hpp"

#include "PugException.hpp"

using namespace std;

namespace pugcpp
{
namespace exceptions
{
using namespace tmpl;
using namespace parser::node;

class PugCompilerException : public PugException
{
  public:
    PugCompilerException(const Node &nd, shared_ptr<ITemplateLoader> templateLoader, std::exception *e);
    PugCompilerException(const Node &nd, shared_ptr<ITemplateLoader> templateLoader, const string &message);
};
} // namespace exceptions
} // namespace pugcpp
#endif
