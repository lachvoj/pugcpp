#ifndef IfConditionNode_hpp
#define IfConditionNode_hpp

#include <string>

#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
class IfConditionNode : public Node
{
  private:
    bool defaultNode_ = false;
    bool isInverse_ = false;

  public:
    IfConditionNode(const string &condition, int lineNumber);

    const bool isDefault() const;
    void setDefault(const bool defaultNode);
    const bool isInverse() const;
    void setInverse(const bool isInverse);

    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};

} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // IfConditionNode_hpp