#include "BlockCommentNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
BlockCommentNode::BlockCommentNode() : Node(e_BlockCommentNode)
{
}

bool BlockCommentNode::isBuffered()
{
    return buffered_;
}

void BlockCommentNode::setBuffered(bool buffered)
{
    buffered_ = buffered;
}

void BlockCommentNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    if (!buffered_)
        return;

    if (writer.isPp())
        writer.prettyIndent(1, true);
    writer.append("<!--" + value_);
    block_->execute(writer, model, tmplt);
    if (writer.isPp())
        writer.prettyIndent(1, true);
    writer.append("-->");
}
} // namespace node
} // namespace parser
} // namespace pugcpp