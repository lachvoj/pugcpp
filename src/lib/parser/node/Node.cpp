#include "Node.hpp"

#include <stdexcept>

#include "../../compiler/IndentWriter.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
void Node::setLineNumber(int lineNumber)
{
    m_nLlineNumber = lineNumber;
}

int Node::getLineNumber() const
{
    return m_nLlineNumber;
}

void Node::setValue(const string &value)
{
    m_sValue = value;
}

const string &Node::getValue() const
{
    return m_sValue;
}

void Node::setName(const string &name)
{
    m_sName = name;
}

const string &Node::getName() const
{
    return m_sName;
}

void Node::push(shared_ptr<Node> node)
{
    if (node == nullptr)
        throw runtime_error("Null node!");

    m_clNodes.push_front(node);
}

void Node::setNodes(list<shared_ptr<Node>> &nodes)
{
    m_clNodes = nodes;
}

const list<shared_ptr<Node>> &Node::getNodes()
{
    return m_clNodes;
}

shared_ptr<Node> Node::pollNode()
{
    if (m_clNodes.empty())
        return nullptr;

    shared_ptr<Node> ret = m_clNodes.front();
    m_clNodes.pop_front();

    return ret;
}

bool Node::hasNodes()
{
    return !m_clNodes.empty();
}

bool Node::hasBlock()
{
    return m_pBlock != nullptr;
}

void Node::setBlock(shared_ptr<Node> block)
{
    m_pBlock = block;
}

shared_ptr<Node> Node::getBlock()
{
    return m_pBlock;
}

void Node::setFileName(const string &fileName)
{
    m_sFileName = fileName;
}

const string &Node::getFileName() const
{
    return m_sFileName;
}

shared_ptr<Node> Node::clone()
{
    // TODO: check this!!!
    shared_ptr<Node> clone(this);
    return clone;
}

} // namespace node
} // namespace parser
} // namespace pugcpp
