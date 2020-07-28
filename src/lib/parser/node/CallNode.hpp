#ifndef CallNode_hpp
#define CallNode_hpp

#include <list>

#include "AttrsNode.hpp"
// #include "../../compiler/IndentWriter.hpp"
// #include "../../model/PugModel.hpp"
// #include "../../template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
class CallNode : public AttrsNode
{
  private:
    bool dynamicMixins_ = false;
    bool call_ = false;

  protected:
    list<string> arguments_;
    CallNode(NodeType type);

  public:
    CallNode();
    list<string> &getArguments();
    void setArguments(const string &arguments);
    bool isCall();
    void setCall(bool call);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
