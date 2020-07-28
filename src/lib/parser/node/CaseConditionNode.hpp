#ifndef CaseConditionNode_hpp
#define CaseConditionNode_hpp

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class CaseConditionNode : public Node
{
  private:
    bool defaultNode_ = false;
  public:
    CaseConditionNode();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
    bool isDefault();
    void setDefault(bool defaultNode);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
