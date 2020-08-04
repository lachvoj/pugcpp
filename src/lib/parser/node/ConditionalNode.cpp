#include "ConditionalNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{

ConditionalNode::ConditionalNode() : Node(e_ContionalNode)
{
}

vector<shared_ptr<IfConditionNode>> &ConditionalNode::getConditions()
{
    return conditions_;
}

void ConditionalNode::setConditions(const vector<shared_ptr<IfConditionNode>> &conditions)
{
    conditions_ = move(conditions);
}

bool ConditionalNode::checkCondition(
    PugModel &model,
    const string &condition,
    shared_ptr<IExpressionHandler> expressionHandler)
{
    return expressionHandler->evaluateBooleanExpression(condition, model);
}

void ConditionalNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    for (auto &conditionNode : conditions_)
    {
        try
        {
            if (conditionNode->isDefault() ||
                checkCondition(model, conditionNode->getValue(), tmplt.getExpressionHandler()) ^
                    conditionNode->isInverse())
            {
                conditionNode->getBlock()->execute(writer, model, tmplt);
                return;
            }
        }
        catch (ExpressionException &e)
        {
            throw PugCompilerException(*conditionNode, tmplt.getTemplateLoader(), &e);
        }
    }
}
} // namespace node
} // namespace parser
} // namespace pugcpp