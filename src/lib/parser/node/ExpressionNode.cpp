#include "./ExpressionNode.hpp"

#include "../../expression/IExpressionHandler.hpp"
#include "../../template/PugTemplate.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{

ExpressionNode::ExpressionNode() : Node(e_ExpressionNode)
{
}

void ExpressionNode::setEscape(bool escape)
{
    escape_ = escape;
}

void ExpressionNode::setBuffer(bool buffer)
{
    buffer_ = buffer;
}

void ExpressionNode::setValue(const string &value)
{
    Node::setValue(StringUtils::trim(value));
}

void ExpressionNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    try
    {
        any res = tmplt.getExpressionHandler()->evaluateExpression(value_, model);
        if (!res.has_value() || !buffer_)
            return;

        // TODO any to string

        if (hasBlock())
        {
            writer.increment();
            block_->execute(writer, model, tmplt);
            writer.decrement();
            writer.newline();
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