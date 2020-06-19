#pragma once

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

class PugCompilerException : PugException
{
  public:
    PugCompilerException(const Node &nd, shared_ptr<ITemplateLoader> templateLoader, const std::exception *e);
    PugCompilerException(const Node &nd, shared_ptr<ITemplateLoader> templateLoader, const string &message);
};
} // namespace exceptions
} // namespace pugcpp
