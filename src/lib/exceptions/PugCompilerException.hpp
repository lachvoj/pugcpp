#pragma once

#include <string>
#include <memory>

#include "PugException.hpp"
#include "../parser/node/Node.hpp"
#include "../template/ITemplateLoader.hpp"

using namespace std;


namespace exceptions
{
class PugCompilerException: PugException
{
  public:
    PugCompilerException(const parserNode::Node &nd, shared_ptr<tmpl::ITemplateLoader> &templateLoader, const string &message);
    ~PugCompilerException(){}
};
} // namespace exceptions
