#ifndef BlockNode_hpp
#define BlockNode_hpp

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class BlockNode : public Node
{
  private:
  public:
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
