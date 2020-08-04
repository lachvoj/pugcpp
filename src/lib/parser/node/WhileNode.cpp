#include "WhileNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
WhileNode::WhileNode() : Node(e_WhileNode)
{
}

void WhileNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    try
    {
        model.pushScope();
        while (tmplt.getExpressionHandler()->evaluateBooleanExpression(value_, model))
        {
            block_->execute(writer, model, tmplt);
        }
        model.popScope();
    }
    catch (ExpressionException &e)
    {
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
}
} // namespace node
} // namespace parser
} // namespace pugcpp
