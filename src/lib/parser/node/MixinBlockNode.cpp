#include "MixinBlockNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{

MixinBlockNode::MixinBlockNode() : Node(e_MixinBlockNode)
{
}

void MixinBlockNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    vector<shared_ptr<Node>> &nodes = getNodes();
    if (nodes.size() != 1)
        return;

    shared_ptr<Node> &node = nodes[0];
    if (node)
        node->execute(writer, model, tmplt);
}
} // namespace node
} // namespace parser
} // namespace pugcpp
