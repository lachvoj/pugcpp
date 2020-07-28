#include "./CommentNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
CommentNode::CommentNode() : Node(e_CommentNode)
{
}

bool CommentNode::isBuffered()
{
    return buffered_;
}

void CommentNode::setBuffered(bool buffered)
{
    buffered_ = buffered;
}

void CommentNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    if (!buffered_)
        return;

    if (writer.isPp())
        writer.prettyIndent(1, true);
    writer.append("<!--" + value_ + "-->");
}
} // namespace node
} // namespace parser
} // namespace pugcpp