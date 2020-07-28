#ifndef DoctypeNode_hpp
#define DoctypeNode_hpp

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class DoctypeNode : public Node
{
  public:
    DoctypeNode();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
