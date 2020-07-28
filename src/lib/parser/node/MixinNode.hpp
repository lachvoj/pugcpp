#ifndef MixinNode_hpp
#define MixinNode_hpp

#include "CallNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class MixinNode : public CallNode
{
  private:
    string rest_;

  public:
    MixinNode();
    void setRest(const string &reset);
    const string &getRest() const;
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
