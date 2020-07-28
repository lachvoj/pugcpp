#include "./AssigmentNode.hpp"

#include "../../expression/IExpressionHandler.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
AssigmentNode::AssigmentNode() : Node(e_AssignmentNode)
{
}

void AssigmentNode::execute(compiler::IndentWriter &writer, model::PugModel &model, tmpl::PugTemplate &tmplt)
{
    any res;
    try
    {
        res = tmplt.getExpressionHandler()->evaluateExpression(value_, model);
    }
    catch (exceptions::ExpressionException &e)
    {
        throw exceptions::PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
    model.put(name_, res);
}

} // namespace node
} // namespace parser
} // namespace pugcpp
