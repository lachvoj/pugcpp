#ifndef Compiler_hpp
#define Compiler_hpp

#include <memory>

#include "../exceptions/Exception.hpp"
#include "../model/PugModel.hpp"
#include "../parser/node/Node.hpp"
#include "../template/PugTemplate.hpp"

#include "IndentWriter.hpp"

using namespace std;

namespace pugcpp
{
// forward declarations
namespace tmpl
{
class PugTemplate;
}
namespace expression
{
class IExpressionHandler;
}
namespace model
{
class PugModel;
}
namespace parser
{
namespace node
{
class Node;
}
} // namespace parser

namespace compiler
{
using namespace parser::node;
using namespace tmpl;
using namespace model;
using namespace exceptions;

class Compiler
{
  private:
    shared_ptr<Node> rootNode_;
    bool prettyPrint_ = false;
    PugTemplate *template_;

  public:
    Compiler(shared_ptr<Node> rootNode);
    Compiler(shared_ptr<Node> rootNode, PugTemplate *tmplt);
    Compiler(shared_ptr<Node> rootNode, PugTemplate *tmplt, bool prettyPrint);

    string compileToString(PugModel &model);
    void compile(PugModel &model, ostringstream &w);
    void setPrettyPrint(bool prettyPrint);
    void setTemplate(PugTemplate *pugTemplate);
};
} // namespace compiler
} // namespace pugcpp
#endif
