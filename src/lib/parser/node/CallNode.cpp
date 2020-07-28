#include "./CallNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
CallNode::CallNode() : AttrsNode(e_CallNode)
{
}

CallNode::CallNode(NodeType type) : AttrsNode(type)
{
}

list<string> &CallNode::getArguments()
{
    return arguments_;
}

void CallNode::setArguments(const string &arguments)
{
    arguments_.clear();
}

bool CallNode::isCall()
{
    return call_;
}

void CallNode::setCall(bool call)
{
    call_ = call;
}

void CallNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
}
} // namespace node
} // namespace parser
} // namespace pugcpp
