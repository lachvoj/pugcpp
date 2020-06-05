#pragma once

#include <memory>

#include "../parser/node/Node.hpp"
#include "../template/PugTemplate.hpp"
#include "../expression/IExpressionHandler.hpp"
#include "../model/PugModel.hpp"

using namespace std;

namespace compiler
{
class Compiler
{
private:
    shared_ptr<parserNode::Node> m_pRootNode;
    bool m_bPrettyPrint;
    shared_ptr<tmpl::PugTemplate> m_pTemplate;
    shared_ptr<expression::IExpressionHandler> m_pExpressionHandler;

public:
    Compiler(shared_ptr<parserNode::Node> rootNode);
    ~Compiler();

    string compileToString(const model::PugModel &model) throw
};
}
