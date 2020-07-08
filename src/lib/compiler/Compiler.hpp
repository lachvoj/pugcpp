#ifndef Compiler_hpp
#define Compiler_hpp

#include <memory>

#include "../expression/IExpressionHandler.hpp"
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
using namespace expression;
using namespace model;

class Compiler
{
  private:
    shared_ptr<Node> m_pRootNode;
    bool m_bPrettyPrint;
    shared_ptr<PugTemplate> m_pTemplate;
    shared_ptr<IExpressionHandler> m_pExpressionHandler;

  public:
    Compiler(shared_ptr<Node> rootNode);

    string compileToString(PugModel &model);
    void compile(PugModel &model, stringstream &w);
    void setPrettyPrint(bool prettyPrint);
    void setTemplate(shared_ptr<PugTemplate> pugTemplate);
    void setExpressionHandler(shared_ptr<IExpressionHandler> expressionHandler);
};
} // namespace compiler
} // namespace pugcpp
#endif
