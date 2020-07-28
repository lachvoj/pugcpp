#include "TagNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
const set<string> TagNode::inlineTags_ = {"a",
                                     "abbr",
                                     "acronym",
                                     "b",
                                     "br",
                                     "code",
                                     "em",
                                     "font",
                                     "i",
                                     "img",
                                     "ins",
                                     "kbd",
                                     "map",
                                     "samp",
                                     "small",
                                     "span",
                                     "strong",
                                     "sub",
                                     "sup"};

TagNode::TagNode(NodeType type) : AttrsNode(type)
{
    block_ = static_pointer_cast<Node>(make_shared<BlockNode>());
}

TagNode::TagNode() : TagNode(e_TagNode)
{
}

bool TagNode::hasTextNode()
{
    return bool(textNode_);
}

shared_ptr<Node> TagNode::getTextNode()
{
    return textNode_;
}

void TagNode::setTextNode(shared_ptr<Node> textNode)
{
    textNode_ = textNode;
}

bool TagNode::isInline()
{
    return (inlineTags_.find(name_) != inlineTags_.end());
}

bool TagNode::isInline(const Node &node)
{
    // Recurse if the node is a block
    if (node.getType() == e_BlockNode)
    {
        return everyIsInline(const_cast<Node &>(node).getNodes());
    }
    return (node.getType() == e_TextNode || inlineTags_.find(node.getName()) != inlineTags_.end());
}

bool TagNode::canInline()
{
    if (!block_)
        return true;

    vector<shared_ptr<Node>> &nodes = block_->getNodes();

    // Empty tag
    if (nodes.empty())
        return true;

    // Text-only or inline-only tag
    if (nodes.size() == 1)
        return isInline(*(nodes.front()));

    // Multi-line inline-only tag
    if (everyIsInline(nodes))
    {
        for (vector<shared_ptr<Node>>::iterator it = nodes.begin() + 1; it != nodes.end(); ++it)
        {
            if ((*(it - 1))->getType() == e_TextNode && (*it)->getType() == e_TextNode)
                return false;
        }
        return true;
    }

    // Mixed tag
    return false;
}

bool TagNode::isBuffer()
{
    return buffer_;
}

void TagNode::setBuffer(bool buffer)
{
    buffer_ = buffer;
}

void TagNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    writer.increment();

    if (!writer.isCompiledTag())
    {
        // if (!writer.isCompiledDoctype() && "html".equals(name))
        // {
        //     //              template.setDoctype(null);
        // }
        writer.setCompiledTag(true);
    }

    if ("pre" == name_)
    {
        writer.setEscape(true);
    }
    if (writer.isPp() && !isInline())
    {
        writer.prettyIndent(0, true);
    }
    if (isSelfClosing() || isSelfClosing(tmplt))
    {
        writer.append("<");
        writer.append(bufferName(tmplt, model));
        writer.append(visitAttributes(model, tmplt));
        isTerese(tmplt) ? writer.append(">") : writer.append("/>");
    }
    else
    {
        writer.append("<");
        writer.append(bufferName(tmplt, model));
        writer.append(visitAttributes(model, tmplt));
        writer.append(">");
        if (hasCodeNode())
            codeNode_->execute(writer, model, tmplt);
        if (hasBlock())
            block_->execute(writer, model, tmplt);
        // pretty print
        if (writer.isPp() && !isInline() && "pre" != name_ && !canInline())
            writer.prettyIndent(0, true);
        writer.append("</");
        writer.append(bufferName(tmplt, model));
        writer.append(">");
    }
    if ("pre" == name_)
        writer.setEscape(false);
    writer.decrement();
}

bool TagNode::everyIsInline(const vector<shared_ptr<Node>> &nodes)
{
    bool multilineInlineOnlyTag = true;
    for (const auto &node : nodes)
    {
        if (!isInline(*node))
        {
            multilineInlineOnlyTag = false;
            break;
        }
    }

    return multilineInlineOnlyTag;
}

string TagNode::bufferName(PugTemplate &tmplt, PugModel &model)
{
    if (!buffer_)
        return name_;

    try
    {
        return tmplt.getExpressionHandler()->evaluateStringExpression(name_, model);
    }
    catch (const std::exception &e)
    {
        // TODO
    }

    return "";
}

} // namespace node
} // namespace parser
} // namespace pugcpp