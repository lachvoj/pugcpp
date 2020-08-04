#include "./IfConditionNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
IfConditionNode::IfConditionNode(const string &condition, int lineNumber) : Node(e_IfConditionNode)
{
    value_ = condition;
    lineNumber_ = lineNumber;
}

const bool IfConditionNode::isDefault() const
{
    return defaultNode_;
}

void IfConditionNode::setDefault(const bool defaultNode)
{
    defaultNode_ = defaultNode;
}

const bool IfConditionNode::isInverse() const
{
    return isInverse_;
}

void IfConditionNode::setInverse(const bool isInverse)
{
    isInverse_ = isInverse;
}

void IfConditionNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    block_->execute(writer, model, tmplt);
}

} // namespace node
} // namespace parser
} // namespace pugcpp