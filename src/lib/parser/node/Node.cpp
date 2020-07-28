#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
Node::Node(NodeType type) : type_(type)
{
}

const NodeType Node::getType() const
{
    return type_;
}

void Node::setLineNumber(int lineNumber)
{
    lineNumber_ = lineNumber;
}

int Node::getLineNumber() const
{
    return lineNumber_;
}

void Node::setValue(const string &value)
{
    value_ = value;
}

const string &Node::getValue() const
{
    return value_;
}

void Node::setName(const string &name)
{
    name_ = name;
}

const string &Node::getName() const
{
    return name_;
}

void Node::push(const shared_ptr<Node> &node)
{
    if (!node)
        throw runtime_error("Null node!");

    nodes_.push_back(node);
}

void Node::setNodes(vector<shared_ptr<Node>> &nodes)
{
    nodes_ = nodes;
}

vector<shared_ptr<Node>> &Node::getNodes()
{
    return nodes_;
}

shared_ptr<Node> Node::pollNode()
{
    shared_ptr<Node> ret;

    if (nodes_.empty())
        return ret;

    ret = nodes_.front();
    nodes_.erase(nodes_.begin());

    return ret;
}

bool Node::hasNodes()
{
    return !nodes_.empty();
}

bool Node::hasBlock()
{
    return block_ != nullptr;
}

void Node::setBlock(const shared_ptr<Node> &block)
{
    block_ = block;
}

shared_ptr<Node> Node::getBlock()
{
    return block_;
}

void Node::setFileName(const string &fileName)
{
    fileName_ = &fileName;
}

void Node::setFileName(string const *fileName)
{
    fileName_ = fileName;
}

const string &Node::getFileName() const
{
    return *fileName_;
}

shared_ptr<Node> Node::clone()
{
    // TODO:
}

} // namespace node
} // namespace parser
} // namespace pugcpp
