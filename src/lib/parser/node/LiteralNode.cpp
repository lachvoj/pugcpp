#include "LiteralNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
LiteralNode::LiteralNode() : Node(e_LiteralNode)
{
}

void LiteralNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    writer.append(value_);
}
} // namespace node
} // namespace parser
} // namespace pugcpp