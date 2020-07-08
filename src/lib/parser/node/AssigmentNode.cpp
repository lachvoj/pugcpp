#include "AssigmentNode.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
void AssigmentNode::execute(compiler::IndentWriter &writer, model::PugModel &model, tmpl::PugTemplate &tmplt)
{
    any res;
    try
    {
        res = tmplt.getExpressionHandler()->evaluateExpression(m_sValue, model);
    }
    catch (const exceptions::ExpressionException &e)
    {
        throw exceptions::PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
    model.put(m_sName, res);
}

} // namespace node
} // namespace parser
} // namespace pugcpp
