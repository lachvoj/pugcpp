#ifndef LiteralNode_hpp
#define LiteralNode_hpp

#include "../../compiler/IndentWriter.hpp"

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class LiteralNode : public Node
{
  public:
    LiteralNode();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // LiteralNode_hpp
