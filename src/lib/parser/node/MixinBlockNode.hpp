#ifndef MixinBlockNode_hpp
#define MixinBlockNode_hpp

#include <memory>
#include <vector>

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class MixinBlockNode : public Node
{
  public:
    MixinBlockNode();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // MixinBlockNode_hpp
