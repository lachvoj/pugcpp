#ifndef TagNode_hpp
#define TagNode_hpp

#include <algorithm>
#include <set>
#include <vector>

#include "../../compiler/IndentWriter.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

#include "AttrsNode.hpp"
#include "BlockNode.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{

class TagNode : public AttrsNode
{
  private:
    static const set<string> inlineTags_;
    shared_ptr<Node> textNode_;
    bool buffer_ = false;

  protected:
    TagNode(NodeType type);

  private:
    bool everyIsInline(const vector<shared_ptr<Node>> &nodes);
    string bufferName(PugTemplate &tmplt, PugModel &model);

  public:
    TagNode();
    bool hasTextNode();
    shared_ptr<Node> getTextNode();
    void setTextNode(shared_ptr<Node> textNode);
    bool isInline();
    bool isInline(const Node &node);
    bool canInline();
    bool isBuffer();
    void setBuffer(bool buffer);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
