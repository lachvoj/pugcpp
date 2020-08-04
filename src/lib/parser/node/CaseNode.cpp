#include "./CaseNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
CaseNode::When::When() : Node(e_WhenNode)
{
}

void CaseNode::When::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    block_->execute(writer, model, tmplt);
}

CaseNode::CaseNode() : Node(e_CaseNode)
{
}

vector<shared_ptr<CaseConditionNode>> &CaseNode::getCaseConditionNodes()
{
    return caseConditionNodes_;
}

void CaseNode::setConditions(const vector<shared_ptr<CaseConditionNode>> &caseConditionNodes)
{
    caseConditionNodes_ = caseConditionNodes;
}

bool CaseNode::checkCondition(
    PugModel &model,
    shared_ptr<Node> &caseConditionNode,
    IExpressionHandler &expressionHandler)
{
    return expressionHandler.evaluateBooleanExpression(value_ + "==" + caseConditionNode->getValue(), model);
}

void CaseNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    try
    {
        bool skip = false;
        for (auto &when : block_->getNodes())
        {
            if (skip || "default" == when->getValue() || checkCondition(model, when, *(tmplt.getExpressionHandler())))
            {
                skip = false;
                if (when->getBlock())
                {
                    when->execute(writer, model, tmplt);
                }
                else
                {
                    skip = true;
                }
            }
        }
    }
    catch (ExpressionException &e)
    {
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
}

} // namespace node
} // namespace parser
} // namespace pugcpp
