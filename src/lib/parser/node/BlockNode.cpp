#include "./BlockNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
BlockNode::BlockNode() : Node(e_BlockNode)
{
}

bool BlockNode::isYield()
{
    return yield_;
}

void BlockNode::setYield(bool yield)
{
    yield_ = yield;
}

shared_ptr<BlockNode> BlockNode::getYieldBlock()
{
    return yieldBlock_;
}

void BlockNode::setYieldBlock(shared_ptr<BlockNode> yieldBlock)
{
    yieldBlock_ = yieldBlock;
}

const string &BlockNode::getMode()
{
    return mode_;
}

void BlockNode::setMode(const string &mode)
{
    mode_ = mode;
}

vector<shared_ptr<Node>> &BlockNode::getPrepended()
{
    return prepended_;
}

void BlockNode::setPrepended(vector<shared_ptr<Node>> &prepended)
{
    prepended_ = prepended;
}

vector<shared_ptr<Node>> &BlockNode::getAppended()
{
    return appended_;
}

void BlockNode::setAppended(vector<shared_ptr<Node>> &appended)
{
    appended_ = appended;
}

shared_ptr<Parser> BlockNode::getParser()
{
    return parser_;
}

void BlockNode::setParser(shared_ptr<Parser> parser)
{
    parser_ = parser;
}

bool BlockNode::isSubBlock()
{
    return subBlock_;
}

void BlockNode::setSubBlock(bool subBlock)
{
    subBlock_ = subBlock;
}

BlockNode &BlockNode::getIncludeBlock()
{
    BlockNode &ret = *this;
    for (auto &node : nodes_)
    {
        NodeType type = node->getType();
        if (type == e_BlockNode && static_pointer_cast<BlockNode>(node)->isYield())
        {
            return *(static_pointer_cast<BlockNode>(node));
        }
        else if (type == e_TagNode && static_pointer_cast<TagNode>(node)->isTextOnly())
        {
            continue;
        }
        else if (type == e_BlockNode && &(static_pointer_cast<BlockNode>(node)->getIncludeBlock()) != this)
        {
            ret = static_pointer_cast<BlockNode>(node)->getIncludeBlock();
        }
        else if (node->hasBlock())
        {
            ret = static_pointer_cast<BlockNode>(node->getBlock())->getIncludeBlock();
        }
        if (ret.getType() == e_BlockNode && static_cast<BlockNode>(ret).isYield())
        {
            return ret;
        }
    }

    return ret;
}

void BlockNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    if (writer.isPp() && nodes_.size() > 1 && !writer.isEscape() && nodes_[0]->getType() == e_TextNode &&
        nodes_[1]->getType() == e_TextNode)
    {
        writer.prettyIndent(1, true);
    }

    for (int i = 0; i < nodes_.size(); ++i)
    {
        // Pretty print text
        if (writer.isPp() && i > 0 && !writer.isEscape() && nodes_[i]->getType() == e_TextNode &&
            nodes_[i - 1]->getType() == e_TextNode)
        {
            writer.prettyIndent(1, false);
        }

        nodes_[i]->execute(writer, model, tmplt);
        // Multiple text nodes are separated by newlines
        shared_ptr<Node> nextNode;
        if (i + 1 < nodes_.size())
            nextNode = nodes_[i + 1];
        if (nextNode && nodes_[i]->getType() == e_TextNode && nextNode->getType() == e_TextNode)
            writer.append("\n");
    }
}
} // namespace node
} // namespace parser
} // namespace pugcpp