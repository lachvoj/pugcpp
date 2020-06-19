#pragma once

#include <memory>

#include "../expression/IExpressionHandler.hpp"
#include "../model/PugModel.hpp"
#include "../parser/node/Node.hpp"
#include "../template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
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
