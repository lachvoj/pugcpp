#include "./ExpressionNode.hpp"

#include "../../expression/IExpressionHandler.hpp"
#include "../../template/PugTemplate.hpp"
#include "../../util/StringUtils.hpp"

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

        string str;
        if (int *resi = any_cast<int>(&res))
            str = to_string(*resi);
        else if (double *resd = any_cast<double>(&res))
        {
            str = to_string(*resd);
            str.erase(str.find_last_not_of('0') + 1, string::npos);
        }
        else if (string *ress = any_cast<string>(&res))
            str = *ress;
        else
            throw ExpressionException("Unknown type.");
        if (escape_)
            StringUtils::escapeHtml4(str);
        writer.append(str);

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