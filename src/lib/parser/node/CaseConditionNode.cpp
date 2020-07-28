#include "CaseConditionNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
CaseConditionNode::CaseConditionNode() : Node(e_CaseConditionNode)
{
}

void CaseConditionNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    block_->execute(writer, model, tmplt);
}

bool CaseConditionNode::isDefault()
{
    return defaultNode_;
}

void CaseConditionNode::setDefault(bool defaultNode)
{
    defaultNode_ = defaultNode;
}

} // namespace node
} // namespace parser
} // namespace pugcpp
