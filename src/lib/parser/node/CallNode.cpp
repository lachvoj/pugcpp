#include "./CallNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
list<string> &CallNode::getArguments()
{
    return m_conArguments;
}

void CallNode::setArguments(const string &arguments)
{
    m_conArguments.clear();
}

bool CallNode::isCall()
{
    return m_bCall;
}

void CallNode::setCall(bool call)
{
    m_bCall = call;
}

void CallNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
}
} // namespace node
} // namespace parser
} // namespace pugcpp
