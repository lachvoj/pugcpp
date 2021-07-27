#ifndef CallNode_hpp
#define CallNode_hpp

#include <list>

#include "../../compiler/IndentWriter.hpp"
#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"
#include "../../util/ArgumentSplitter.hpp"

#include "Attr.hpp"
#include "AttrsNode.hpp"
#include "ConditionalNode.hpp"
#include "IfConditionNode.hpp"
#include "MixinBlockNode.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace util;
using namespace exceptions;

class CallNode : public AttrsNode
{
  private:
    bool dynamicMixins_ = false;
    bool call_ = false;

    void getInjectionPoints(vector<shared_ptr<MixinBlockNode>> &ret, const shared_ptr<Node> &block);
    void writeVariables(PugModel &model, MixinNode &mixin, PugTemplate &tmplt);
    void writeAttributes(PugModel &model, MixinNode &mixin, PugTemplate &tmplt);

  protected:
    vector<string> arguments_;
    CallNode(NodeType type);

  public:
    CallNode();
    vector<string> &getArguments();
    void setArguments(const vector<string> &arguments);
    void setArguments(const string &arguments);
    bool isCall();
    void setCall(bool call);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
