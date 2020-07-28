#include "./DoctypeNode.hpp"

#include "../../template/PugTemplate.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
DoctypeNode::DoctypeNode() : Node(e_DoctypeNode)
{
}

void DoctypeNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    tmplt.setDoctype(value_);
    writer.append(tmplt.getDoctypeLine());
    writer.setCompiledDoctype(true);
}
} // namespace node
} // namespace parser
} // namespace pugcpp